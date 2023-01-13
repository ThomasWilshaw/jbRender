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
			for each (Edge * edge in poly->GetEdges()) {
				for each (Edge * test_edge in edge_list_) {
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
		std::vector<vec3> edges_divided_by_w = edge->GetEdgeDividedByW();
		frame_->MoveTo(edges_divided_by_w.at(0));
		frame_->DrawTo(edges_divided_by_w.at(1));
	}
	
	return true;
}