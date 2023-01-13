// jbRender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "frame.h"
#include "maths.h"
#include "object.h"
#include "stack.h"
#include "tokenizer.h"

using namespace Imf;
using namespace Imath;



int main()
{
    Frame frame(1920, 1080, Rgba(1.0, 1.0, 1.0, 1.0));

    Tokenizer t("..\\..\\..\\program.jbr", &frame);

    if (frame.WriteFrame()) {
        std::cout << "Frame written" << std::endl;
    }
    else {
        std::cout << "Error";
    }

    
}
