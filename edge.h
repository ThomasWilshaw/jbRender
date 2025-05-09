#ifndef EDGE_H
#define EDGE_H
#include "maths.h"
// Stores an edge as two vec4
class Edge
{
public:
	Edge(vec4 a, vec4 b);

	vec4 GetA();
	vec4 GetB();

	std::vector<vec3> GetEdgeDividedByW();

	bool Compare(const Edge* e) const;

	void SetBoundary(bool boundary) { boundary_ = boundary; };
	bool GetBoundary() { return boundary_; };

	void PrintEdge();

private:
	std::vector<vec4> vertices_;
	bool boundary_;

};

#endif
