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

	vec4 outside = {2.0, 2.0, 1.0, 1.0};
	std::cout << "Point outside of plane returns (0): " << renderer.FaceVertexCompare(poly, outside) << std::endl;

	vec4 infront_of_plane = { 0.0, 0.0, -0.1, 1.0 };
	std::cout << "Point infront of plane returns (0): " << renderer.FaceVertexCompare(poly, infront_of_plane) << std::endl;

	vec4 behind_plane = { 0.0, 0.0, 0.1, 1.0 };
	std::cout << "Point behind plane returns (1): " << renderer.FaceVertexCompare(poly, behind_plane) << std::endl;

	vec4 on_plane = {0.0, 0.0, 0.0, 1.0};
	std::cout << "Point on plane returns (0): " << renderer.FaceVertexCompare(poly, on_plane) << std::endl;

	vec4 infront_of_vertex = {1.0, 1.0, -0.1, 1.0};
	std::cout << "Point infront of vertex returns (0): " << renderer.FaceVertexCompare(poly, infront_of_vertex) << std::endl;

	vec4 behind_vertex = { -1.0, 1.0, 0.1, 1.0 };
	std::cout << "Point behind vertex returns (1): " << renderer.FaceVertexCompare(poly, behind_vertex) << std::endl;

	std::cout << "Poly Normal: " << poly->GetScreenNormal().x << "," << poly->GetScreenNormal().y << "," << poly->GetScreenNormal().z << std::endl;

	vec4 infront_but_close = {0.999, 0.998, -0.1, 1.0};
	std::cout << "Point infront of plane and close to vertex returns (0): " << renderer.FaceVertexCompare(poly, infront_but_close) << std::endl;

	vec4 behind_by_a_small_amount = { 0.0, 0.0, 0.000001, 1.0 };
	std::cout << "Point only just behind plane returns (1):" << renderer.FaceVertexCompare(poly, behind_by_a_small_amount) << std::endl;

	vec4 infront_by_a_small_amount = { 0.0, 0.0, -0.000001, 1.0 };
	std::cout << "Point only just infront of plane returns (0):" << renderer.FaceVertexCompare(poly, infront_by_a_small_amount) << std::endl;





	return 0;
}