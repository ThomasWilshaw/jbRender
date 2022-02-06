#ifndef STACK_H
#define STACK_H

#include <vector>

#include "maths.h"

class Stack
{
public:
	Stack();

	void Push(Matrix m);

	Matrix Pop();

private:
	std::vector<Matrix> stack_;
};

#endif
