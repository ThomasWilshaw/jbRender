#include "edge.h"

Edge::Edge(vec4 a, vec4 b) :
	boundary_(true)
{
	vertices_.push_back(a);
	vertices_.push_back(b);

	double size_a = magnitude(a);
	double size_b = magnitude(b);

	hash_key_ = new std::vector<vec4>();

	size_a < size_b ? hash_key_->push_back(a) : hash_key_->push_back(b);
	size_b > size_a ? hash_key_->push_back(b) : hash_key_->push_back(a);
}

bool Edge::Compare(const Edge* e) const
{
	if (hash_key_->size() != 2) {
		return false;
	}

	if (hash_key_->at(0).x != e->hash_key_->at(0).x) {
		return false;
	}
	if (hash_key_->at(0).y != e->hash_key_->at(0).y) {
		return false;
	}
	if (hash_key_->at(0).z != e->hash_key_->at(0).z) {
		return false;
	}
	if (hash_key_->at(0).w != e->hash_key_->at(0).w) {
		return false;
	}

	if (hash_key_->at(1).x != e->hash_key_->at(1).x) {
		return false;
	}
	if (hash_key_->at(1).y != e->hash_key_->at(1).y) {
		return false;
	}
	if (hash_key_->at(1).z != e->hash_key_->at(1).z) {
		return false;
	}
	if (hash_key_->at(1).w != e->hash_key_->at(1).w) {
		return false;
	}

	return true;
}

vec4 Edge::GetA()
{
	return vertices_.at(0);
}

vec4 Edge::GetB()
{
	return vertices_.at(1);
}

// Ignores divide by 0 error
std::vector <vec3> Edge::GetEdgeDividedByW()
{
	std::vector<vec3> new_edge;
	vec3 a;
	a.x = vertices_.at(0).x / vertices_.at(0).w;
	a.y = vertices_.at(0).y / vertices_.at(0).w;
	a.z = vertices_.at(0).z / vertices_.at(0).w;

	new_edge.push_back(a);

	vec3 b;
	b.x = vertices_.at(1).x / vertices_.at(1).w;
	b.y = vertices_.at(1).y / vertices_.at(1).w;
	b.z = vertices_.at(1).z / vertices_.at(1).w;

	new_edge.push_back(b);

	return new_edge;
}