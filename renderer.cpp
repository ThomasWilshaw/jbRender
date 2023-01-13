#include "renderer.h"

Renderer::Renderer(Scene* scene, Frame* frame) :
	scene_(scene),
	frame_(frame)
{

}

bool Renderer::Render()
{
	frame_->DrawScene(scene_);
	
	return true;
}