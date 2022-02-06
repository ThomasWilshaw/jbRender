#ifndef MATHS_H
#define MATHS_H

#include <vector>

#define PI 3.14159265

struct vec3 {
	double x;
	double y;
	double z;
};

struct vec4 {
	double x;
	double y;
	double z;
	double w;
};

struct poly {
	std::vector<int> verts;
	int vert_count;
};


/*
* Matricies are stored in a row major order 
* m[row][column]
*/
class Matrix
{
public:
	Matrix();

	void SetIdentity();
	void SetData(std::vector< std::vector<double> >);
	void SetPerspective(double alpha, double zn, double zf);

	void PrintMatrix() const;

	std::vector< std::vector<double> > data();

	/*
	* Mupltiply htis matrix by T
	* m = TC
	*/
	void Multiply(Matrix T);

	static double deg_to_rad(double x) {
		double i = 180.0;
		return (x * PI) / i;
	}

private:
	std::vector< std::vector<double> > data_;
};


// static functions

static vec4 TransformVector(vec4 v, Matrix C) {
	vec4 output;

	output.x = v.x * C.data()[0][0] + v.y * C.data()[1][0] + v.z * C.data()[2][0] + v.w * C.data()[3][0];
	output.y = v.x * C.data()[0][1] + v.y * C.data()[1][1] + v.z * C.data()[2][1] + v.w * C.data()[3][1];
	output.z = v.x * C.data()[0][2] + v.y * C.data()[1][2] + v.z * C.data()[2][2] + v.w * C.data()[3][2];
	output.w = v.x * C.data()[0][3] + v.y * C.data()[1][3] + v.z * C.data()[2][3] + v.w * C.data()[3][3];

	return output;
}

static vec4 TransformVector(vec3 v, Matrix C)
{
	vec4 v4;
	v4.x = v.x;
	v4.y = v.y;
	v4.z = v.z;
	v4.w = 1.0;
	
	return TransformVector(v4, C);
}

#endif
