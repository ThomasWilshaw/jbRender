#include <iostream>
#include "renderer.h"

int main(int argc, char** argv)
{
	std::cout << "-Face vertex compare test-" << std::endl;

	Scene* scene = new Scene();
	Frame* frame = new Frame(100, 100, Imf::Rgba(1.0, 1.0, 1.0, 1.0));
	Renderer renderer(scene, frame);

	std::cout << "--- CROSS IN MDDLE ---" << std::endl;

	vec4 a = { -1.0, -1.0,  1.0, 1.0 };
	vec4 b = { 1.0, -1.0, 0.0, 1.0 };
	vec4 c = { 1.0, 1.0, 1.0, 1.0 };
	vec4 d = { -1.0, 1.0, 0.0, 1.0 };

	Edge* x = new Edge(a, c);
	Edge* y = new Edge(b, d);

	x->PrintEdge();
	y->PrintEdge();

	Renderer::Intersection intersection = renderer.EdgeEdgeCompare(x, y);
	std::cout << "Intersection: " << intersection.alpha << ", " << intersection.deltaIQ << ", " << intersection.valid;




	return 0;
}