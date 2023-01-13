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

private:
    Scene* scene_;
    Frame* frame_;

    std::vector<Edge*> edge_list_;
    std::vector<Edge*> boundary_edges_;
};
