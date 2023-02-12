#include "polygon.h"

Polygon::Polygon() :
	cull_(false)
{
}

void Polygon::AddEdge(Edge* edge)
{
	edges_.push_back(edge);
}

std::vector<Edge*> Polygon::GetEdges()
{
	return edges_;
}

void Polygon::AddVertex(vec4 vertex)
{
	vertices_.push_back(vertex);
}

// Screen space back face cull test
bool Polygon::CullTest()
{
	double sum = 0;
	vec3 n;
	vec3 n_plus_one;

	for (int i = 0; i < vertices_.size(); i++) {
		n = DivideByW(vertices_.at(i));
		if (i < vertices_.size() - 1) {
			n_plus_one = DivideByW(vertices_.at(i + 1));
		}
		else {
			n_plus_one = DivideByW(vertices_.at(0));
		}

		sum += (n_plus_one.x - n.x) * (n_plus_one.y + n.y);
	}

	if (sum > 0) {
		cull_ = true;
		return true;
	}
	else {
		cull_ = false;
		return false;
	}
}

vec3 Polygon::GetScreenNormal()
{
	vec3 p1 = DivideByW(vertices_.at(0));
	vec3 p2 = DivideByW(vertices_.at(1));
	vec3 p3 = DivideByW(vertices_.at(2));

	vec3 u = Vec3Subtract(p2, p1);
	vec3 v = Vec3Subtract(p3, p1);

	vec3 cross = Vec3Cross(u, v);
	double mag = magnitude(cross);

	vec3 result = { cross.x / mag, cross.y / mag, cross.z / mag };

	return result;
}

bool Polygon::ContainsEdge(Edge* edge)
{
	for each (Edge * test_edge in edges_) {
		if (edge->Compare(test_edge)) {
			return true;
		}
	}

	return false;
}

vec4 Polygon::PointOnPlane()
{
	vec4 point;

	vec4 diff = Vec4Subtract(vertices_.at(1), vertices_.at(0));

	point.x = vertices_.at(0).x + 0.5 * diff.x;
	point.y = vertices_.at(0).y + 0.5 * diff.y;
	point.z = vertices_.at(0).z + 0.5 * diff.z;
	point.w = vertices_.at(0).w + 0.5 * diff.w;

	
	return point;
}
