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

// Stores an edge as two vec4
class Edge
{
public:
	Edge(vec4 a, vec4 b);

	vec4 GetA();
	vec4 GetB();

	std::vector<vec3> GetEdgeDividedByW();

	std::vector<vec4>* GetHashKey() { return hash_key_; };

	bool Compare(const Edge* e) const;

private:
	std::vector<vec4> vertices_;
	std::vector<vec4>* hash_key_;

};

// Stores a polygon as a list of edges and vertices
class Polygon
{
public:
	Polygon();

	void AddEdge(Edge* edge);

	std::vector<Edge*> GetEdges();

	void AddVertex(vec4 vertex);
	std::vector<vec4> GetScreenSpaceVertices() { return vertices_; };

	bool CullTest();
	bool GetCull() { return cull_; };

private:
	std::vector<Edge*> edges_;
	std::vector<vec4> vertices_;

	bool cull_;
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

#endif
