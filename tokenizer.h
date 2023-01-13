#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "frame.h"
#include"object.h"
#include "stack.h"
#include "Scene.h"

// Reads the .jb file and builds the scene
class Tokenizer
{
public:
	Tokenizer(const std::string filename, Frame* frame);

private:
	void LoadObjects();
	void DrawObject(std::string obj);
	Object* GetObjectFromName(std::string obj);

	std::vector<Object*> obj_list_;

	Frame* frame_;
	Matrix* C;
	Stack stack_;
	Scene *scene_;
};

#endif
