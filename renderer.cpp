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
	}

	// Draw Edges
	for each (Edge * edge in edge_list_) {
		int QI = 0;
		for each (Polygon * poly in scene_->GetPolygons()) {
			if (!poly->GetCull()) {
				if (FaceVertexCompare(poly, edge->GetB())) {
					QI++;
				}
			}
		}
		std::cout << "Edge QI: " << QI << std::endl;
		
		if (QI == 0) {
			std::vector<vec3> edges_divided_by_w = edge->GetEdgeDividedByW();
			frame_->MoveTo(edges_divided_by_w.at(0));
			frame_->DrawTo(edges_divided_by_w.at(1));
		}
		
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
		vec3 point_on_plane = DivideByW(poly->GetVertices().at(0));

		double z = ((-normal.x * (v.x - point_on_plane.x) - normal.y * (v.y - point_on_plane.y)) / normal.z) + point_on_plane.z;

		if (z > v.z) {
			return true;
		}
	}
	return false;
}