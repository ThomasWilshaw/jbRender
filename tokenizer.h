#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "frame.h"
#include"object.h"
#include "stack.h"

class Tokenizer
{
public:
	Tokenizer(const std::string filename, Frame* frame);

private:
	void LoadObjects();
	void DrawObject(std::string obj);

	std::vector<Object> obj_list_;

	Frame* frame_;
	Matrix C;
	Stack stack_;
};

#endif
