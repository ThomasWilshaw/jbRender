#include <iostream>

#include "stack.h"

Stack::Stack()
{
}

void Stack::Push(Matrix m)
{
	stack_.push_back(m);
}

Matrix Stack::Pop()
{
	Matrix m;
	if (stack_.size() > 0) {
		m = stack_.back();
		stack_.pop_back();
		return m;
	} else {
		std::cout << "ERROR: ried to pop empty stack. Returning Identity matrix" << std::endl;
		m.SetIdentity();
		return m;
	}
}