#include "Scene.h"

Scene::Scene()
{}

void Scene::AddObject(Object* object, Matrix *C, bool wireframe)
{
	for (int i = 0; i < object->PolyCount(); i++) {
		Polygon* polygon = new Polygon();

		if (wireframe) {
			polygon->SetWireframe(true);
		}

		// Polygon stores a list of vertices and a list edges which point to them
		vec4* transformed_vector_a;
		vec4* transformed_vector_b;

		// Create first vertex and addto polygon
		transformed_vector_a = TransformVector(object->Vert(i, 0), C);
		polygon->AddVertex(transformed_vector_a);

		// Save pointer to first vertex
		vec4* first_vertex = transformed_vector_a;

		// Loop through remaining vertices and add each new vertex and edge
		for (int j = 1; j < object->Polys()[i].vert_count; j++) {
			transformed_vector_b = TransformVector(object->Vert(i, j), C);

			polygon->AddVertex(transformed_vector_b);

			Edge* edge = new Edge(transformed_vector_a, transformed_vector_b);
			if (wireframe) {
				edge->SetWireframe(true);
			}
			polygon->AddEdge(edge);

			transformed_vector_a = transformed_vector_b;
		}

		// Add final edge
		Edge* final_edge = new Edge(transformed_vector_a, first_vertex);
		if (wireframe) {
			final_edge->SetWireframe(true);
		}

		polygon->AddEdge(final_edge);

		scene_polys_.push_back(polygon);
	}
}

void Scene::Clear()
{
	for (auto edge : scene_edges_) {
		for (auto vert : edge->GetVerticies()) {
			delete vert;
		}
		delete edge;
	}
	scene_edges_.clear();

	for (auto polygon : scene_polys_) {
		polygon->GetVertices().clear();
		delete polygon;
	}
	scene_polys_.clear();


}
