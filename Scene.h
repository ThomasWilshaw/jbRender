#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <unordered_map>

#include "data.h"
#include "maths.h"
#include "object.h"

// Stores all the actual polygons in their transformed state.
class Scene
{
public:
	Scene();

	// Adds the object vertices and polygons to the scene's lists
	// Doesn't handle edges
	void AddObject(std::string object, Matrix* C, bool wireframe);

	std::vector<polygon> GetPolygons() { return scene_polys_; };

	// Unique objects in scene
	std::unordered_map<std::string, Object*> scene_objects_;

	vertices scene_vertices_;
	std::vector<polygon> scene_polys_;
	int current_object_offset_;
	int object_count_;

};

#endif //SCENE_H
