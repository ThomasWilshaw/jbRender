#include "Scene.h"

Scene::Scene() :
	current_object_number_(0)
{}

void Scene::AddObject(std::string object_name, Matrix *C, bool wireframe)
{
	Object* object = scene_objects_.at(object_name);

	int polygon_offset = current_object_number_ * object->Vertices().x.size();

	// Copy vertices into scene vertices and transform them via matrix C
	for (int i = 0; i < object->Vertices().x.size(); i++) {
		double x = object->Vertices().x[i];
		double y = object->Vertices().y[i];
		double z = object->Vertices().z[i];
		double w = object->Vertices().w[i];

		TransformVector(&x, &y, &z, &w, C);

		scene_vertices_.x.push_back(x);
		scene_vertices_.y.push_back(y);
		scene_vertices_.z.push_back(z);
		scene_vertices_.w.push_back(w);
	}

	// Copy objects polygons into the scenes polygon list and
	// update the polygons data and flags
	for (int poly = 0; poly < object->PolyCount(); poly++) {
		polygon new_polygon;

		if (wireframe) {
			new_polygon.wire = true;
		}

		new_polygon.object_offset = polygon_offset;
		new_polygon.vertices = object->Polygons()[poly].vertices;
		new_polygon.cull = false;

		scene_polys_.push_back(new_polygon);
	}
}
