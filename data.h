#ifndef DATA_H
#define DATA_H

#include <vector>

#include "maths.h"


// Stores a set or vertices as a struct of arrays
struct vertices
{
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
	std::vector<double> w;
};

// Stores a polygon as a list of vertex indices
// Also includes flags cull and wire
struct polygon
{
	std::vector<int> vertices; // Index of vertices
	int object_offset;         // Offset in Scene vertex list for this polygons object
	bool cull;                 // To cull or not to cull?
	bool wire;                 // Render as wireframe
};

// Stores a list of edges as two arrays of end points vertex indexes
struct edges
{
	std::vector<int> a;
	std::vector<int> b;
	std::vector<bool> boundary;
};

inline int GetVertexRealIndex(polygon poly, int index)
{
	return poly.vertices[index] + poly.object_offset;
}

vec4 GetVertexFromPolygon(polygon poly, vertices vertex_list, int index);

// Return a list of edge indexe pairs for a given polygon
edges GetEdgesFromPolygon(polygon poly);

// Back face cull test
// Does not assume projection transform has been done
bool CullTest(polygon poly, vertices verts);

// Compare to edges to see if they are the same
bool EdgeCompare(int a_1, int b_1, int a_2, int b_2);

// Return the vec4 at verts[index]
vec4 Vec4FromVertexList(int index, vertices verts);

// Check if the given polygon contains the given edge
bool PolygonContainsEdge(polygon poly, int a, int b);

// Calculate the screen normal of a polygon
vec3 PolygonScreenNormal(polygon poly, vertices vertex_list);


#endif // DATA_H