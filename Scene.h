#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "maths.h"
#include "object.h"

struct Edge {
	vec3 p1;
	vec3 p2;
};

struct Poly {
	std::vector<Edge> edges;
};

class Scene
{
public:
	Scene();

	void AddObject(Object* object);


private:
	std::vector<Edge> scene_edges_;
	std::vector<Poly> scene_polys_;

};

#endif //SCENE_H
