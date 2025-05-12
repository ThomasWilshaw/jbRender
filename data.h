#ifndef DATA_H
#define DATA_H

#include <vector>


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

// Stores a list of edges as two arrays of end points
struct edges
{
	std::vector<int> a;
	std::vector<int> b;
};


#endif // DATA_H