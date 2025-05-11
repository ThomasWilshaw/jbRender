#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "edge.h"
#include "edge.h"
#include "maths.h"
#include "object.h"
#include "polygon.h"


// Stores all the actual polygons in their transformed state.
class Scene
{
public:
	Scene();

	void AddObject(Object* object, Matrix* C, bool wireframe);

	void Clear();

	std::vector<Edge*> GetEdges() { return scene_edges_; };
	std::vector<Polygon*> GetPolygons() { return scene_polys_; };


private:
	std::vector<Edge*> scene_edges_;
	std::vector<Polygon*> scene_polys_;

};

#endif //SCENE_H
