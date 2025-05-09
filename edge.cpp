#include "edge.h"

Edge::Edge(vec4 a, vec4 b) :
	boundary_(true)
{
	vertices_.push_back(a);
	vertices_.push_back(b);

	double size_a = magnitude(a);
	double size_b = magnitude(b);
}

bool Edge::Compare(const Edge* e) const
{
	if (Vec4Compare(vertices_.at(0), e->vertices_.at(0))) {
		if (Vec4Compare(vertices_.at(1), e->vertices_.at(1))) {
			return true;
		}
	}
	else if (Vec4Compare(vertices_.at(1), e->vertices_.at(0))) {
		if (Vec4Compare(vertices_.at(0), e->vertices_.at(1))) {
			return true;
		}
	}
	else {
		return false;
	}
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

void Edge::PrintEdge(bool divide_by_w)
{
	float div_a, div_b;
	if (divide_by_w) {
		div_a = vertices_.at(0).w;
		div_b = vertices_.at(1).w;
	}
	else {
		div_a = 1.0;
		div_b = 1.0;
	}
	std::cout << "(";
	std::cout << vertices_.at(0).x / div_a;
	std::cout << ", ";
	std::cout << vertices_.at(0).y / div_a;
	std::cout << ", ";
	std::cout << vertices_.at(0).z / div_a;
	std::cout << ")";

	std::cout << " -> ";

	std::cout << "(";
	std::cout << vertices_.at(1).x / div_b;
	std::cout << ", ";
	std::cout << vertices_.at(1).y / div_b;
	std::cout << ", ";
	std::cout << vertices_.at(1).z / div_b;
	std::cout << ")";

	std::cout << std::endl;
}
