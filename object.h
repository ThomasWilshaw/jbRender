#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "maths.h"

class Object
{
public:
	Object(const std::string filename);

	void PrintVerts();
	void PrintPolys();

private:
	std::vector<vec3> verts_;
	std::vector<poly> polys_;
};


#endif
