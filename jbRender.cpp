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

    Renderer* engine = new Renderer(scene, &frame);

    Tokenizer t("..\\..\\..\\program.jbr", scene, engine);
    
    engine->Render();

    if (frame.WriteFrame("D:\\src\\jbRender\\render\\out_.exr")) {
        std::cout << "Frame written" << std::endl;
    }
    else {
        std::cout << "Error";
    }
}
