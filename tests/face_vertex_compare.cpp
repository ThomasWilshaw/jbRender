#include <iostream>
#include "renderer.h"

int main(int argc, char** argv)
{
	std::cout << "-Face vertex compare test-" << std::endl;

	Scene* scene = new Scene();
	Frame* frame = new Frame(100, 100, Imf::Rgba(1.0, 1.0, 1.0, 1.0));
	Renderer renderer(scene, frame);

	vec4 a = { -1.0, -1.0,  0.0, 1.0 };
	vec4 b = { 1.0, -1.0, 0.0, 1.0 };
	vec4 c = { 1.0, 1.0, 0.0, 1.0 };
	vec4 d = { -1.0, 1.0, 0.0, 1.0 };

	Edge* x = new Edge(a, b);
	Edge* y = new Edge(b, c);
	Edge* z = new Edge(c, d);
	Edge* w = new Edge(d, a);

	Polygon* poly = new Polygon();

	poly->AddVertex(a);
	poly->AddVertex(b);
	poly->AddVertex(c);
	poly->AddVertex(d);

	poly->AddEdge(x);
	poly->AddEdge(y);
	poly->AddEdge(z);
	poly->AddEdge(w);

	poly->CullTest();

	std::cout << "Cull test: " << poly->GetCull() << std::endl;

	vec4 infront_of_plane = { 0.0, 0.0, 0.1, 1.0 };

	std::cout << "Point infront of plane: " << renderer.FaceVertexCompare(poly, infront_of_plane);


	return 0;
}