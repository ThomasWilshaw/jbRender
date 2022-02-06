#ifndef MATHS_H
#define MATHS_H

#include <vector>

struct vec3 {
	double x;
	double y;
	double z;
};

struct vev4 {
	double x;
	double y;
	double z;
	double w;
};

struct poly {
	std::vector<int> verts;
	int vert_count;
};

#endif

