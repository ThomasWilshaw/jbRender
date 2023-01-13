#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "maths.h"
#include "object.h"

// Stores all the actual polygons in their transformed state.
class Scene
{
public:
	Scene();

	void AddObject(Object* object, Matrix* C);

	std::vector<Edge*> GetEdges() { return scene_edges_; };
	std::vector<Polygon*> GetPolygons() { return scene_polys_; };
	std::vector<Edge*> GetDividedEdges() { return divided_by_w_edges_; };


private:
	std::vector<Edge*> scene_edges_;
	std::vector<Polygon*> scene_polys_;

	std::vector<Edge*> divided_by_w_edges_;

};

#endif //SCENE_H
