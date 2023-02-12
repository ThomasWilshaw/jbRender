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

	std::vector<vec4>* GetHashKey() { return hash_key_; };

	bool Compare(const Edge* e) const;

	void SetBoundary(bool boundary) { boundary_ = boundary; };
	bool GetBoundary() { return boundary_; };

private:
	std::vector<vec4> vertices_;
	std::vector<vec4>* hash_key_;
	bool boundary_;

};

#endif
