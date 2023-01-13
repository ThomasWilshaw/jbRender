// jbRender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "frame.h"
#include "maths.h"
#include "object.h"
#include "renderer.h"
#include "Scene.h"
#include "stack.h"
#include "tokenizer.h"

using namespace Imf;
using namespace Imath;



int main()
{
    Frame frame(1920, 1080, Rgba(1.0, 1.0, 1.0, 1.0));

    Scene* scene = new Scene();

    Tokenizer t("..\\..\\..\\program.jbr", scene);

    Renderer engine(scene, &frame);
    engine.Render();

    if (frame.WriteFrame()) {
        std::cout << "Frame written" << std::endl;
    }
    else {
        std::cout << "Error";
    }
}
