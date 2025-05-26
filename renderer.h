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

    bool FaceVertexCompare(const polygon& poly, vec4 vertex);

    std::map<double, int> BoundaryEdgeCompare(int a, int b);
    
    Intersection EdgeEdgeCompare(int a_1, int b_1, int a_2, int b_2);

    void Clear();

private:
    
    //double EdgeEdgeCompare(Edge* a, Edge* b);

    Scene* scene_;
    Frame* frame_;

    int frame_number_;

    edges edge_list_;
    edges boundary_edges_;

    vertices w_scaled_verts_;
};

#endif
