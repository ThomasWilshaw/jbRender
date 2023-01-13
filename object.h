#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "maths.h"

// Basic data stored about an object loaded from file
class Object
{
public:
	Object(const std::string filename);

	int PolyCount();
	int VertCount() { return verts_.size(); };

	std::vector<poly> Polys();
	std::vector<vec3> Verts() { return verts_; };

	vec3 Vert(int i) { return verts_[i]; };

	vec3 Vert(int poly, int vert) {
		return verts_[Polys()[poly].verts[vert]];
	}

	void PrintVerts();
	void PrintPolys();

private:
	std::vector<vec3> verts_;
	std::vector<poly> polys_;
};


#endif
