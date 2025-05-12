#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "maths.h"
#include "data.h"

// Basic data stored about an object loaded from file
class Object
{
public:
	Object(const std::string filename);

	int PolyCount();
	int VerticiesCount() { return verts_.x.size(); };

	std::vector<polygon> Polygons() { return polys_; };
	vertices Vertices() { return verts_; };

	//vec3 Vertex(int i);
	//vec3 Vertex(int poly, int vert);

	void PrintVerts();
	void PrintPolys();

private:
	vertices verts_;
	std::vector<polygon> polys_;
};


#endif
