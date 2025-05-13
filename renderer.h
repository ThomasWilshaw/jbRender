#ifndef RENDERER_H
#define RENDERER_H

#include "frame.h"
#include "maths.h"
#include "Scene.h"

#include <map>
#include <vector>

#include "data.h"

// Renders a Scene. Takes a Scene and a Frame
class Renderer
{
public:
    struct Intersection {
        double alpha;
        int deltaIQ;
        bool valid;
    };

    Renderer::Renderer(Scene* scene, Frame* frame);

    void Render();

    void SaveImage();

    //bool FaceVertexCompare(Polygon* poly, vec4* vertex);

    //std::map<double, int> BoundaryEdgeCompare(Edge* edge);
    
    //Intersection EdgeEdgeCompare(Edge* edge, Edge* test_edge);

private:
    
    //double EdgeEdgeCompare(Edge* a, Edge* b);

    Scene* scene_;
    Frame* frame_;

    int frame_number_;

    edges edge_list_;
    edges boundary_edges_;
};

#endif
