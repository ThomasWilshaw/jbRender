#ifndef MATHS_H
#define MATHS_H

#include <vector>
#include <iostream>

#define PI 3.14159265

// Vector of length 3
struct vec3 {
	double x;
	double y;
	double z;
};

// Vector of length 4
struct vec4 {
	double x;
	double y;
	double z;
	double w;
};

//Ver simple polygon structure used by Object class to store raw polygon data
struct poly {
	std::vector<int> verts;
	int vert_count;
};

// Axis enum for rotation matrix
enum axis {
	kAxisX,
	kAxisY,
	kAxisZ
};

/*
* Matricies are stored in a row major order 
* m[row][column]
*/
class Matrix
{
public:
	Matrix();

	// Sets matrix to identitiy
	void SetIdentity();

	// Allows you to manually set the data of a matrix
	void SetData(std::vector< std::vector<double> >);

	// Functions for creating transform matricies

	void SetPerspective(double alpha, double zn, double zf);
	void SetTranslate(double x, double y, double z);
	void SetScale(double x, double y, double z);
	void SetRotation(double theta, axis j);

	void PrintMatrix() const;

	// Acces the matricies raw data
	std::vector< std::vector<double> > data();

	/*
	* Mupltiply this matrix by T
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
// Multiply a vec4 by a 4x4 matrix
static vec4 TransformVector(vec4 v, Matrix* C) {
	struct vec4 output = {0, 0, 0, 1};

	output.x = v.x * C->data()[0][0] + v.y * C->data()[1][0] + v.z * C->data()[2][0] + v.w * C->data()[3][0];
	output.y = v.x * C->data()[0][1] + v.y * C->data()[1][1] + v.z * C->data()[2][1] + v.w * C->data()[3][1];
	output.z = v.x * C->data()[0][2] + v.y * C->data()[1][2] + v.z * C->data()[2][2] + v.w * C->data()[3][2];
	output.w = v.x * C->data()[0][3] + v.y * C->data()[1][3] + v.z * C->data()[2][3] + v.w * C->data()[3][3];

	return output;
}

// Multiply a vec3 by a 4x4 matrix (setw w to 1.0)
static vec4 TransformVector(vec3 v, Matrix* C)
{
	vec4 v4;
	v4.x = v.x;
	v4.y = v.y;
	v4.z = v.z;
	v4.w = 1.0;
	
	return TransformVector(v4, C);
}

// Divide a vec4 by w. REturns a vec3
static vec3 DivideByW(vec4 v)
{
	vec3 output;
	if (v.w != 0) {
		output.x = v.x / v.w;
		output.y = v.y / v.w;
		output.z = v.z / v.w;
	} else {
		std::cout << "ERROR: DivideByW is divind by 0";
		output.x = v.x;
		output.y = v.y;
		output.z = v.z;
	}

	return output;
}

static double magnitude(vec4 v)
{
	double sum;
	sum = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;

	return sqrt(sum);
}

static double magnitude(vec3 v)
{
	vec4 temp = { v.x, v.y, v.z, 0.0 };
	return magnitude(temp);;
}

static vec3 Vec3Subtract(vec3 a, vec3 b)
{
	vec3 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return result;
}

static vec4 Vec4Subtract(vec4 a, vec4 b)
{
	vec4 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;

	return result;
}

static void Vec3Print(vec3 v)
{
	std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

static void Vec3Print(vec4 v)
{
	vec3 temp = { v.x, v.y, v.z };
	Vec3Print(temp);
}

static vec3 Vec3Cross(vec3 a, vec3 b)
{
	vec3 result = { 0.0, 0.0, 0.0};

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	//Vec3Print(result);
	return result;
}

static bool Vec4Compare(vec4 a, vec4 b)
{
	bool x = a.x == b.x;
	bool y = a.y == b.y;
	bool z = a.z == b.z;
	bool w = a.w == b.w;

	return x && y && z && w;
}



#endif
