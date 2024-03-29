#ifndef POLYGON_H
#define POLYGON_H

#include "edge.h"
#include "maths.h"


// Stores a polygon as a list of edges and vertices
class Polygon
{
public:
	Polygon();

	void AddEdge(Edge* edge);

	std::vector<Edge*> GetEdges();

	void AddVertex(vec4 vertex);
	std::vector<vec4> GetVertices() { return vertices_; };

	bool CullTest();
	bool GetCull() { return cull_; };

	vec3 GetScreenNormal();

	bool ContainsEdge(Edge* edge);

	vec4 PointOnPlane();

private:
	std::vector<Edge*> edges_;
	std::vector<vec4> vertices_;

	bool cull_;
};

#endif
