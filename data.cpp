#include "data.h"


vec4 GetVertexFromPolygon(polygon poly, vertices vertex_list, int index)
{
	vec4 out;
	int real_index = poly.vertices[index] + poly.object_offset;

	out.x = vertex_list.x[real_index];
	out.y = vertex_list.y[real_index];
	out.z = vertex_list.z[real_index];
	out.w = vertex_list.w[real_index];

	return out;
}

// Return a list of edge indexe pairs for a given polygon
edges GetEdgesFromPolygon(polygon poly, vertices vertex_list)
{
	int point_a, point_b;
	edges polygon_edge_list;

	point_a = GetVertexRealIndex(poly, 0);

	for (int i = 1; i < poly.vertices.size(); i++) {
		point_b = GetVertexRealIndex(poly, i);

		polygon_edge_list.a.push_back(point_a);
		polygon_edge_list.b.push_back(point_b);

		point_a = point_b;
	}

	polygon_edge_list.a.push_back(point_a);
	polygon_edge_list.b.push_back(GetVertexRealIndex(poly, 0));

	return polygon_edge_list;
}

// Back face cull test
// Does not assume projection transform has been done
bool CullTest(polygon poly, vertices verts)
{
	double sum = 0;
	vec4 n;
	vec4 n_plus_one;

	for (int i = 0; i < poly.vertices.size(); i++) {
		n = GetVertexFromPolygon(poly, verts, i);
		if (i < poly.vertices.size() - 1) {
			n_plus_one = GetVertexFromPolygon(poly, verts, i + 1);
		}
		else {
			n_plus_one = GetVertexFromPolygon(poly, verts, 0);
		}

		sum += (n_plus_one.x - n.x) * (n_plus_one.y + n.y);
	}

	if (sum > 0) {
		poly.cull = true;
		return true;
	}
	else {
		poly.cull = false;
		return false;
	}
}

// Compare to edges to see if they are the same
bool EdgeCompare(int a_1, int b_1, int a_2, int b_2)
{
	if (a_1 == b_1 && a_2 == b_2) {
		return true;
	}
	if (a_1 == b_2 && a_2 == b_1) {
		return true;
	}
	return false;
}

vec4 Vec4FromVertexList(int index, vertices verts)
{
	vec4 out;
	out.x = verts.x[index];
	out.y = verts.y[index];
	out.z = verts.z[index];
	out.w = verts.w[index];

	return out;
}