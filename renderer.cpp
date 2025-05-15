#include "renderer.h"
#include "timer.h"

Renderer::Renderer(Scene* scene, Frame* frame) :
	scene_(scene),
	frame_(frame),
	frame_number_(0)
{

}

void Renderer::Render()
{
	std::cout << std::to_string(scene_->scene_vertices_.x.size()) << std::endl;
	Timer t1("Full render");
	// Divide out w component
	for (int i = 0; i < scene_->scene_vertices_.x.size(); i++) {
		// Maybe slow?
		if (scene_->scene_vertices_.w[i] == 0.0) {
			std::cout << "Warning: divide by zero error in projection transform" << std::endl;
		}
		scene_->scene_vertices_.x[i] /= scene_->scene_vertices_.w[i];
		scene_->scene_vertices_.y[i] /= scene_->scene_vertices_.w[i];
		scene_->scene_vertices_.z[i] /= scene_->scene_vertices_.w[i];
	}

	// Cull then build scene and boundary edge lists
	for (auto &polygon : scene_->scene_polys_) {
		// Skip polgons that are culled
		if (!polygon.wire && CullTest(polygon, scene_->scene_vertices_)) {
			polygon.cull = true;
			continue;
		}

		// Add polygon edges to the scene edge list and boundary edge list
		edges polygon_edges = GetEdgesFromPolygon(polygon);
		for (int i = 0; i < polygon_edges.a.size(); i++) {
			// Add first ever edge, only called once
			if (edge_list_.a.empty()) {
				edge_list_.a.push_back(polygon_edges.a[i]);
				edge_list_.b.push_back(polygon_edges.b[i]);
				edge_list_.boundary.push_back(true);
			}
			else {
				// Check if edge is already in edge_list
				bool already_in_list = false;
				for (int j = 0; j < edge_list_.a.size(); j++) {
					// As soon as we find a matching edge set that edge boundary status to be false and break
					if (EdgeCompare(polygon_edges.a[i], polygon_edges.b[i], edge_list_.a[j], edge_list_.b[j])) {
						already_in_list = true;
						edge_list_.boundary[j] = false;
						break;
					}
				}
				// If the edge is not already in the list add it and set its boundary status to true
				if (!already_in_list) {
					edge_list_.a.push_back(polygon_edges.a[i]);
					edge_list_.b.push_back(polygon_edges.b[i]);
					edge_list_.boundary.push_back(true);
				}
			}
		}
	}

	// Generate boundary list
	for (int i = 0; i < edge_list_.a.size(); i++)
	{
		if (edge_list_.boundary[i]) {
			boundary_edges_.a.push_back(edge_list_.a[i]);
			boundary_edges_.b.push_back(edge_list_.b[i]);
		}
	}
	Timer t2("Full render no preprocess");
	// Draw edges
	for (int i = 0; i < edge_list_.a.size(); i++) {
		int a_index = edge_list_.a[i];
		int b_index = edge_list_.b[i];
		vec4 a = Vec4FromVertexList(a_index, scene_->scene_vertices_);
		vec4 b = Vec4FromVertexList(b_index, scene_->scene_vertices_);

		// If rendering a wireframe draw all edges
		if (false) {
			frame_->MoveTo(a);
			frame_->DrawTo(b);

			continue;
		}

		// Generate intersection list
		std::map<double, int> intersection_list = BoundaryEdgeCompare(a_index, b_index);

		// Normal render
		int QI = 0;

		// Initilise QI
		for (const auto &polygon : scene_->scene_polys_) {
			if (!polygon.cull) {
				// Don't compare to own polygon
				if (!PolygonContainsEdge(polygon, a_index, b_index)) {
					if (!polygon.wire) {
						if (FaceVertexCompare(polygon, a)) {
							QI++;
						}
					}
				}
			}
		}

		if (QI == 0) {
			frame_->MoveTo(a);
		}

		std::string sequence = std::to_string(QI);
		bool error = false;

		for (auto it = intersection_list.begin(); it != intersection_list.end(); ++it)
		{
			vec3 new_point;
			new_point.x = a.x + it->first * (b.x - a.x);
			new_point.y = a.y + it->first * (b.y - a.y);
			new_point.z = 0.0;

			if (QI == 1 && it->second == -1) {
				frame_->MoveTo(new_point);
			}
			
			if (QI == 0 && it->second == 1) {
				frame_->DrawTo(new_point);
			}

			QI += it->second;

			sequence += " -> " + std::to_string(QI);

			if (QI < 0) {
				error = true;
			}
		}

		if (QI == 0) {
			frame_->DrawTo(b);
		}
		if (error) {
			std::cout << "---ERROR--- QI < 0" << std::endl;
			//std::cout << sequence << std::endl;
			for (auto it = intersection_list.cbegin(); it != intersection_list.cend(); ++it)
			{
				std::cout << std::to_string(it->first) << " " << std::to_string(it->second) << "|";
			}
			std::cout << std::endl;
			frame_->SetLineColor(Imf::Rgba(1.0, 0.0, 0.0));
			frame_->DrawTo(b);
			frame_->ResetLineColor();
		}
	}

	return;
}

bool Renderer::FaceVertexCompare(const polygon& poly, vec4 vertex)
{
	bool flag = false;

	int index_i = 0;
	int index_i_plus_1 = 0;
	for (int i = 0; i < poly.vertices.size(); i++) {
		index_i = poly.vertices[i];
		index_i_plus_1 = poly.vertices[i+1 == poly.vertices.size() ? 0 : i+1];

		index_i = index_i + poly.object_offset;
		index_i_plus_1 = index_i_plus_1 + poly.object_offset;

		double v_i_y = scene_->scene_vertices_.y[index_i];
		double v_i_plus_1_y = scene_->scene_vertices_.y[index_i_plus_1];

		double v_i_x = scene_->scene_vertices_.x[index_i];
		double v_i_plus_1_x = scene_->scene_vertices_.x[index_i_plus_1];


		double d_i = v_i_y - vertex.y;
		double d_i_plus_1 = v_i_plus_1_y - vertex.y;

		if (signbit(d_i * d_i_plus_1) == 0) {
			continue;
		}

		double d_inf = v_i_plus_1_y - v_i_y;
		double d = (v_i_plus_1_y - vertex.y) * (v_i_x - vertex.x) - (v_i_plus_1_x - vertex.x) * (v_i_y - vertex.y);
		if (signbit(d * d_inf) == 0) {
			continue;
		}

		flag = !flag;
	}

	// If we crossed an edge an odd number of times we are inside the polygon
	// We now test if we are in front or behind it
	if (flag) {
		// Find normal of plane
		// Create vector between point on plane and test point if it were on the plane
		// Dot product normal and this vector and rearrange to find the z of this imaginary point
		// if actual z is greater than imaginary z the point is behind plane as z axis goes away form eye.

		vec3 normal = PolygonScreenNormal(poly, scene_->scene_vertices_);
		vec4 point_on_plane = GetVertexFromPolygon(poly, scene_->scene_vertices_, 0);

		double z = ((normal.x * (vertex.x - point_on_plane.x) + normal.y * (vertex.y - point_on_plane.y)) / -normal.z) + point_on_plane.z;

		if (abs(z - vertex.z) < 0.001) {
			return false;
		}

		if (z < vertex.z) {
			return true;
		}
	}
	return false;
}

Renderer::Intersection Renderer::EdgeEdgeCompare(int a_1, int b_1, int a_2, int b_2)
{
	Renderer::Intersection intersection;
	intersection.valid = false;

	const vec4 p = Vec4FromVertexList(a_1, scene_->scene_vertices_);
	const vec4 q = Vec4FromVertexList(b_1, scene_->scene_vertices_);

	const vec4 r = Vec4FromVertexList(a_2, scene_->scene_vertices_);
	const vec4 s = Vec4FromVertexList(b_2, scene_->scene_vertices_);

	// calculate d_1 and d_2
	double d_1 = (s.x - r.x) * (p.y - r.y) - (p.x - r.x) * (s.y - r.y);
	double d_2 = (s.x - r.x) * (q.y - r.y) - (q.x - r.x) * (s.y - r.y);

	// if signs match return failed intersection
	if (signbit(d_1 * d_2) == 0) {
		return intersection;
	}

	// calculate d_3 and d_4
	double d_3 = (p.x - r.x) * (q.y - r.y) - (q.x - r.x) * (p.y - r.y);
	double d_4 = d_1 - d_2 + d_3;

	// if signs match return failed intersection
	if (signbit(d_3 * d_4) == 0) {
		return intersection;
	}

	// calculate how far along each line we are
	double alpha = d_1 / (d_1 - d_2);
	double beta = d_3 / (d_3 - d_4);

	// If we are at the start or end of either line, return. Maybe wrong?
	if (alpha <= 0 || beta <= 0 || alpha >= 1 || beta >= 1) {
		return intersection;
	}

	double z_i = p.z + alpha * (q.z - p.z);
	double z_j = s.z + (1 - beta) * (r.z - s.z);

	// If we are on the wrong side or on the plane, return
	if (z_i < z_j) {
		return intersection;
	}

	if (abs(z_i - z_j) < 0.001) {
		return intersection;;
	}

	// Otherwise return valid intersection

	int deltaIQ = d_1 < 0 ? 1 : -1;

	intersection.alpha = alpha;
	intersection.deltaIQ = deltaIQ;
	intersection.valid = true;

	return intersection;
}

std::map<double, int> Renderer::BoundaryEdgeCompare(int a, int b)
{
	std::map<double, int> intersection_list;
	int boundary_edge_a;
	int boundary_edge_b;
	for (int i = 0; i < boundary_edges_.a.size(); i++) {
		boundary_edge_a = boundary_edges_.a[i];
		boundary_edge_b = boundary_edges_.b[i];
		if (EdgeCompare(a, b, boundary_edge_a, boundary_edge_b)) {
			continue;
		}

		Renderer::Intersection intersection = EdgeEdgeCompare(a, b, boundary_edge_a, boundary_edge_b);

		if (intersection.valid) {
			intersection_list.emplace(intersection.alpha, intersection.deltaIQ);
		}
	}

	return intersection_list;
}

void Renderer::SaveImage()
{
	std::string path = "D:\\src\\jbRender\\render\\out_" + std::to_string(frame_number_) + ".exr";
	frame_->WriteFrame(path.c_str());
	frame_->ClearFrame();
	/*
	for (auto edge : edge_list_) {
		delete edge;
	}
	edge_list_.clear();

	boundary_edges_.clear();
	*/
	frame_number_++;
}

