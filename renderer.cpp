#include "renderer.h"

Renderer::Renderer(Scene* scene, Frame* frame) :
	scene_(scene),
	frame_(frame),
	wireframe_(false)
{

}

bool Renderer::Render()
{
	// Generate edge list
	for each (Polygon* poly in scene_->GetPolygons()) {
		if (!poly->GetCull()) {
			for each (Edge* edge in poly->GetEdges()) {
				// Add first ever edge
				if (edge_list_.size() == 0) {
					edge_list_.push_back(edge);
				} else {
					// Loop though edges and compare to current edge
					// Only add to list if it isn't already there
					bool exists = false;
					for each (Edge* test_edge in edge_list_) {
						if (edge->Compare(test_edge)) {
							exists = true;
							// If we hit an edge more than once it can't be a boundary edge
							edge->SetBoundary(false);
							test_edge->SetBoundary(false);
						}
					}
					if (!exists) {
						edge_list_.push_back(edge);
					}
				}
			}
		}
	}

	for each (Edge * edge in edge_list_) {
		if (edge->GetBoundary()) {
			boundary_edges_.push_back(edge);
			edge->PrintEdge();
		}
	}
	std::cout << "number of Boundary Edges: " << boundary_edges_.size() << std::endl;

	// Draw Edges
	int edge_count = 0;
	for each (Edge * edge in edge_list_) {
		//std::cout << std::endl << "--- Line: " << ++edge_count  << " ---" << std::endl;
		// Calculate QI
		int QI = 0;
		for each (Polygon * poly in scene_->GetPolygons()) {
			if (!poly->GetCull()) {
				if (!poly->ContainsEdge(edge)) {
					if (FaceVertexCompare(poly, edge->GetA())) {
						QI++;
					}
				}
			}
		}
		//std::cout << "QI: " << QI << std::endl;

		// Find intersections
		//std::vector<Intersection> intersection_list;
		std::map<double, int> intersection_list = BoundaryEdgeCompare(edge);
		
		
		// Draw Edge
		std::vector<vec3> edge_divided_by_w = edge->GetEdgeDividedByW();

		if (wireframe_) {
			if (intersection_list.size() == 0) {
				//continue;
			}
			frame_->MoveTo(edge_divided_by_w.at(0));
			frame_->DrawTo(edge_divided_by_w.at(1));
		}
		else {

			if (QI == 0) {
				frame_->MoveTo(edge_divided_by_w.at(0));
			}

			for (auto it = intersection_list.begin(); it != intersection_list.end(); ++it)
			{
				// it->first = alpha, it->second = deltaIQ
				//std::cout << "alpha: " << it->first << ", deltaIQ: " << it->second << std::endl;

				vec3 new_point;
				new_point.x = edge_divided_by_w.at(0).x + it->first * (edge_divided_by_w.at(1).x - edge_divided_by_w.at(0).x);
				new_point.y = edge_divided_by_w.at(0).y + it->first * (edge_divided_by_w.at(1).y - edge_divided_by_w.at(0).y);
				new_point.z = 0.0;

				if (QI == 1 && it->second == -1) {
					frame_->MoveTo(new_point);
					//QI += it->second;
					//continue;
				}
				else if (QI == 0 && it->second == 1) {
					frame_->DrawTo(new_point);
					//QI += it->second;
					//continue;
				}

				QI += it->second;
				if (QI < 0) {
					std::cout << "---ERROR--- QI < 0" << std::endl;
				}

			}

			if (QI == 0) {
				if (edge->GetBoundary()) {
					frame_->SetLineColor(Imf::Rgba(1.0, 0.0, 0.0));
				}
				frame_->DrawTo(edge_divided_by_w.at(1));
				frame_->ResetLineColor();
			}
		}
		
	}
	
	return true;
}

bool Renderer::FaceVertexCompare(Polygon* poly, vec4 vertex)
{
	bool flag = false;
	vec3 v = DivideByW(vertex);
	bool on_corner = false;

	for each (vec4 test_vertex in poly->GetVertices()) {
		if (vertex.x == test_vertex.x && vertex.y == test_vertex.y) {
			//std::cout << "Vertex on corner" << std::endl;
			flag = true;
			on_corner = true;
			break;
		}
	}

	if (!flag) {
		for each (Edge * edge in poly->GetEdges()) {
			std::vector<vec3> scene_edge = edge->GetEdgeDividedByW();
			vec3 v_i = scene_edge.at(0);
			vec3 v_i_plus_one = scene_edge.at(1);

			double d_i = v_i.y - v.y;
			double d_i_1 = v_i_plus_one.y - v.y;
			if (signbit(d_i * d_i_1) == 0) {
				continue;
			}

			double d_inf = v_i_plus_one.y - v_i.y;
			double d = (v_i_plus_one.y - v.y) * (v_i.x - v.x) - (v_i_plus_one.x - v.x) * (v_i.y - v.y);
			if (signbit(d * d_inf) == 0) {
				continue;
			}

			flag = !flag;
		}
	}

	// If we cross an edge an odd number of times flag is true and we are inside a polygon
	if (flag) {
		// Find normal of plane
		// Create vector between point on plane and test point if it were on the plane
		// Dot product normal and this vector and rearrange to find the z of this imaginary point
		// if actual z is greater than imaginary z the point is behind plane as z axis goes away form eye.

		vec3 normal = poly->GetScreenNormal();
		vec3 point_on_plane = DivideByW(poly->GetVertices().at(0));

		//double z = ((-normal.x * (v.x - point_on_plane.x) - normal.y * (v.y - point_on_plane.y)) / normal.z) + point_on_plane.z;
		double z = ((normal.x * (v.x - point_on_plane.x) + normal.y * (v.y - point_on_plane.y)) / -normal.z) + point_on_plane.z;
		if (on_corner && z != v.z) std::cout << (z - v.z) << std::endl;
		
		// Vec3Print(normal);// std::cout << "DIFF Z: " << z << ", " << v.z << std::endl;
		if (abs(z - v.z) < 0.001) {
			return false;
		}

		if (z < v.z) {
			//std::cout << "DIFF Z: " << z << ", " << v.z << std::endl;
			//Vec3Print(point_on_plane);
			//Vec3Print(v);
			return true;
		}
		//std::cout << "DIFF: " << z << ", " << v.z << std::endl;
	}
	return false;
}

Renderer::Intersection Renderer::EdgeEdgeCompare(Edge* edge, Edge* test_edge)
{
	Renderer::Intersection intersection;
	intersection.valid = false;
	
	std::vector<vec3> a_screen = edge->GetEdgeDividedByW();
	std::vector<vec3> b_screen = test_edge->GetEdgeDividedByW();

	double pz = edge->GetA().z;
	double qz = edge->GetB().z;
	double rz = test_edge->GetA().z;
	double sz = test_edge->GetB().z;

	vec3 p = a_screen.at(0);
	vec3 q = a_screen.at(1);

	vec3 r = b_screen.at(1);
	vec3 s = b_screen.at(0);

	double d_1 = (s.x - r.x) * (p.y - r.y) - (p.x - r.x) * (s.y - r.y);
	double d_2 = (s.x - r.x) * (q.y - r.y) - (q.x - r.x) * (s.y - r.y);

	if (signbit(d_1 * d_2) == 0) {
		return intersection;
	}

	double d_3 = (p.x - r.x) * (q.y - r.y) - (q.x - r.x) * (p.y - r.y);
	double d_4 = d_1 - d_2 + d_3;



	if (signbit(d_3 * d_4) == 0) {
		return intersection;
	}

	//std::cout << "d_1: " << d_1 << " d_2: " << d_2 << " d_3: " << d_3 << " d_4: " << d_4 << std::endl;

	double alpha = d_1 / (d_1 - d_2);
	double beta = d_3 / (d_3 - d_4);
	//std::cout << "alpha: " << alpha << " beta: " << beta << std::endl;

	if (alpha <= 0 || beta <= 0 || alpha >= 1 || beta >= 1) {
		return intersection;
	}
	//std::cout.precision(17);
	//
	double z_i = p.z + alpha * (q.z - p.z);
	double z_j = s.z + (1-beta) * (r.z - s.z);

	//std::cout << "z_i: " << z_i << " z_j:" << z_j << std::endl;
	//Vec3Print(p);
	//Vec3Print(q);
	//Vec3Print(s);
	//Vec3Print(r);

	if (z_i < z_j) {
		return intersection;
	}

	if (alpha == 1.0) {
		//continue;
	}

	if (abs(z_i - z_j) < 0.001) {
		return intersection;;
	}

	//std::cout << "z_i: " << z_i << " z_j:" << z_j << std::endl;
	int deltaIQ = d_1 > 0 ? 1 : -1;
	//std::cout << "d_1: " << d_1 << " d_2: " << d_2 << " d_3: " << d_3 << " d_4: " << d_4 << std::endl;

	intersection.alpha = alpha;
	intersection.deltaIQ = deltaIQ;
	intersection.valid = true;
	
	return intersection;
}

std::map<double, int> Renderer::BoundaryEdgeCompare(Edge* edge)
{
	std::map<double, int> intersection_list;
	for each (Edge * boundary_edge in boundary_edges_) {
		if (edge->Compare(boundary_edge)) {
			continue;
		}
		Renderer::Intersection intersection = EdgeEdgeCompare(edge, boundary_edge);
		
		if (intersection.valid) {
			intersection_list.emplace(intersection.alpha, intersection.deltaIQ);
		}
	}

	return intersection_list;
}
