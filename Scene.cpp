#include "Scene.h"

Scene::Scene()
{}

void Scene::AddObject(Object* object, Matrix *C)
{
	for (int i = 0; i < object->PolyCount(); i++) {
		Polygon* polygon = new Polygon();

		// Edges are added to the Polygon and to the scene so were store a pointer to them here
		std::vector<Edge*> temp_edge_list;
		vec4 transformed_vector_a;
		vec4 transformed_vector_b;

		// Get first vertex
		transformed_vector_a = TransformVector(object->Vert(i, 0), C);
		polygon->AddVertex(transformed_vector_a);

		// Loop through remaining vertices and add each edge
		for (int j = 1; j < object->Polys()[i].vert_count; j++) {
			transformed_vector_b = TransformVector(object->Vert(i, j), C);

			polygon->AddVertex(transformed_vector_b);

			Edge* edge = new Edge(transformed_vector_a, transformed_vector_b);
			polygon->AddEdge(edge);

			transformed_vector_a = transformed_vector_b;

			temp_edge_list.push_back(edge);
		}

		// Add final edge
		transformed_vector_b = TransformVector(object->Vert(i, 0), C);
		Edge* final_edge = new Edge(transformed_vector_a, transformed_vector_b);

		polygon->AddEdge(final_edge);
		temp_edge_list.push_back(final_edge);

		polygon->CullTest();
		//scene_edges_.insert(scene_edges_.end(), temp_edge_list.begin(), temp_edge_list.end());
		scene_polys_.push_back(polygon);
	}
}
