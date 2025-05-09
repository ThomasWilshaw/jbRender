#include "polygon.h"

Polygon::Polygon() :
	cull_(false),
	projection_performed_(false)
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

void Polygon::AddVertex(vec4* vertex)
{
	vertices_.push_back(vertex);
}

void Polygon::ApplyProjectionTransform()
{
	for (auto vertex : GetVertices()) {
		double w = vertex->w;

		if (w == 0.0) {
			std::cout << "Warning: divide by zero error in projection transform" << std::endl;
		}

		vertex->x /= w;
		vertex->y /= w;
		vertex->z /= w;
	}
}

// Back face cull test
// Does not assume projection transform has been done
bool Polygon::CullTest()
{
	double sum = 0;
	vec4 n;
	vec4 n_plus_one;

	for (int i = 0; i < vertices_.size(); i++) {
		n = *vertices_.at(i);
		if (i < vertices_.size() - 1) {
			n_plus_one = *vertices_.at(i + 1);
		}
		else {
			n_plus_one = *vertices_.at(0);
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

// Assumes we have already done projection transform
vec3 Polygon::GetScreenNormal()
{
	const vec4* p1 = vertices_.at(0);
	const vec4* p2 = vertices_.at(1);
	const vec4* p3 = vertices_.at(2);

	vec4 u = Vec4Subtract(*p2, *p1);
	vec4 v = Vec4Subtract(*p3, *p1);

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

	vec4 diff = Vec4Subtract(*vertices_.at(1), *vertices_.at(0));

	point.x = vertices_.at(0)->x + 0.5 * diff.x;
	point.y = vertices_.at(0)->y + 0.5 * diff.y;
	point.z = vertices_.at(0)->z + 0.5 * diff.z;
	point.w = vertices_.at(0)->w + 0.5 * diff.w;

	
	return point;
}
