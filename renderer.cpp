#include "renderer.h"

Renderer::Renderer(Scene* scene, Frame* frame) :
	scene_(scene),
	frame_(frame)
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

	// Generate boundary edges
	/*
	for each (Polygon * poly in scene_->GetPolygons()) {
		if (poly->GetCull()) {
			for each (Edge* edge in poly->GetEdges()) {
				for each (Edge* test_edge in edge_list_) {
					if (edge->Compare(test_edge)) {
						boundary_edges_.push_back(test_edge);
						break;
					}
				}
			}
		}
	}*/

	for each (Edge * edge in edge_list_) {
		if (edge->GetBoundary()) {
			boundary_edges_.push_back(edge);
		}
	}
	std::cout << "number of Boundary Edges: " << boundary_edges_.size() << std::endl;

	// Draw Edges
	for each (Edge * edge in edge_list_) {

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

		std::cout << "QI: " << QI << std::endl;

		// Find intersections
		//std::vector<Intersection> intersection_list;
		std::map<double, int> intersection_list;
		for each(Edge * boundary_edge in boundary_edges_) {
			if (edge->Compare(boundary_edge)) {
				continue;
			}

			std::vector<vec3> a_screen = edge->GetEdgeDividedByW();
			std::vector<vec3> b_screen = boundary_edge->GetEdgeDividedByW();

			double pz = edge->GetA().z;
			double qz = edge->GetB().z;
			double rz = boundary_edge->GetA().z;
			double sz = boundary_edge->GetB().z;

			vec3 p = a_screen.at(0);
			vec3 q = a_screen.at(1);

			vec3 r = b_screen.at(1);
			vec3 s = b_screen.at(0);

			double d_1 = (s.x - r.x) * (p.y - r.y) - (p.x - r.x) * (s.y - r.y);
			double d_2 = (s.x - r.x) * (q.y - r.y) - (q.x - r.x) * (s.y - r.y);

			if (signbit(d_1 * d_2) == 0) {
				continue;
			}

			double d_3 = (p.x - r.x) * (q.y - r.y) - (q.x - r.x) * (p.y - r.y);
			double d_4 = d_1 - d_2 + d_3;

			std::cout << "d_1: " << d_1 << " d_2: " << d_2 << " d_3: " << d_3 << " d_4: " << d_4 << std::endl;

			if (signbit(d_3 * d_4) == 0) {
				continue;
			}

			double alpha = d_1 / (d_1 - d_2);
			double beta = d_3 / (d_3 - d_4);
			

			if (alpha <= 0 || beta <= 0 || alpha >= 1 || beta >= 1) {
				continue;
			}
			//std::cout.precision(17);
			std::cout << "alpha: " << alpha << " beta: " << beta << std::endl;
			double z_i = p.z + alpha * (q.z - p.z);
			double z_j = s.z + beta * (r.z - s.z);

			std::cout << "z_i: " << z_i << " z_j:" << z_j << std::endl;

			if (z_i < z_j) {
				continue;
			}

			if (alpha == 1.0) {
				//continue;
			}

			if (abs(z_i - z_j) < 0.00001) {
				//continue;
			}

			//std::cout << "z_i: " << z_i << " z_j:" << z_j << std::endl;
			int deltaIQ = d_1 > 0 ? 1 : -1;
			std::cout << "d_1: " << d_1 << " d_2: " << d_2 << " d_3: " << d_3 << " d_4: " << d_4 << std::endl;
			intersection_list.emplace(alpha, deltaIQ);
		}
		std::cout << "Intersections: " << intersection_list.size() << std::endl;
		if (intersection_list.size() > 0) {
			for (auto it = intersection_list.begin(); it != intersection_list.end(); ++it)
			{
				std::cout << it->first << '\t' << it->second << std::endl;
			}
		}
		
		// Draw Edge
		std::vector<vec3> edge_divided_by_w = edge->GetEdgeDividedByW();

		if (0) {
			if (intersection_list.size() != 0) {
				continue;
			}
			frame_->MoveTo(edge_divided_by_w.at(0));
			//std::cout << edge_divided_by_w.at(0).x << " " << edge_divided_by_w.at(0).y << " " << edge_divided_by_w.at(0).z << std::endl;
			//std::cout << edge_divided_by_w.at(1).x << " " << edge_divided_by_w.at(1).y << " " << edge_divided_by_w.at(1).y << std::endl;
			frame_->DrawTo(edge_divided_by_w.at(1));
		}
		else {

			if (QI == 0) {
				frame_->MoveTo(edge_divided_by_w.at(0));
			}

			for (auto it = intersection_list.begin(); it != intersection_list.end(); ++it)
			{
				// it->first = alpha, it->second = deltaIQ
				vec3 new_point;
				new_point.x = edge_divided_by_w.at(0).x + it->first * (edge_divided_by_w.at(1).x - edge_divided_by_w.at(0).x);
				new_point.y = edge_divided_by_w.at(0).y + it->first * (edge_divided_by_w.at(1).y - edge_divided_by_w.at(0).y);
				new_point.z = 0.0;

				//std::cout << new_point.x << ", " << new_point.y << ", " << new_point.z << std::endl;

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
				frame_->DrawTo(edge_divided_by_w.at(1));
			}
		}
		std::cout << std::endl;
		
	}
	
	return true;
}

bool Renderer::FaceVertexCompare(Polygon* poly, vec4 vertex)
{
	bool flag = false;
	vec3 v = DivideByW(vertex);

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
		double d     = (v_i_plus_one.y - v.y) * (v_i.x - v.x) - (v_i_plus_one.x - v.x) * (v_i.y - v.y);
		if (signbit(d * d_inf) == 0) {
			continue;
		}

		flag = !flag;
		//std::cout << d_i << ", " << d_i_1 << ", " << d_inf << ", " << d << std::endl;
	}

	// If we cross an edge an odd number of times flag is true and we are inside a polygon
	if (flag) {
		// Find normal of plane
		// Create vector between point on plane and test point if it were on the plane
		// Dot product normal and this vector and rearrange to find the z of this imaginary point
		// if actual z is greater than imaginary z the point is behind plane as z axis goes away form eye.

		/*
		        //normal
				double a = n.t[0];
				double b = n.t[1];
				double c = n.t[2];
				//point on plane;
				double x0 = pList->polys[j].p[0][0];
				double y0 = pList->polys[j].p[0][1];
				double z0 = pList->polys[j].p[0][2];
				//test point
				double x = testP[0];
				double y = testP[1];
				double z = ((-a*(x-x0) - b*(y-y0))/c) + z0;
		*/

		vec3 normal = poly->GetScreenNormal();
		vec3 point_on_plane = DivideByW(poly->GetVertices().at(2));

		double z = ((-normal.x * (v.x - point_on_plane.x) - normal.y * (v.y - point_on_plane.y)) / normal.z) + point_on_plane.z;

		if (abs(z - v.z) < 0.0000001) {
			return false;
		}

		if (z < v.z) {
			//std::cout << "z: " << z << " v.z: " << v.z << std::endl;
			return true;
		}
	}
	return false;
}
