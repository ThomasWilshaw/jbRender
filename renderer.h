#ifndef RENDERER_H
#define RENDERER_H

#include "frame.h"
#include "maths.h"
#include "Scene.h"

#include <map>
#include <vector>

// Renders a Scene. Takes a Scene and a Frame
class Renderer
{
public:
    Renderer::Renderer(Scene* scene, Frame* frame);

    bool Render();

    bool FaceVertexCompare(Polygon* poly, vec4 vertex);

    void SetWireFrameMode(bool b) { wireframe_ = b; };

private:
    
    //double EdgeEdgeCompare(Edge* a, Edge* b);

    Scene* scene_;
    Frame* frame_;

    std::vector<Edge*> edge_list_;
    std::vector<Edge*> boundary_edges_;

    bool wireframe_;
};

#endif
