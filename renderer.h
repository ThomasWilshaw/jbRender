#include "frame.h"
#include "Scene.h"

// Renders a Scene. Takes a Scene and a Frame
class Renderer
{
public:
    Renderer::Renderer(Scene* scene, Frame* frame);

    bool Render();

private:
    Scene* scene_;
    Frame* frame_;
};
