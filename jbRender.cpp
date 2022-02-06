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
    /*

    Object pyramid("objects/square_based_pyramid.obj");
    Object cube("objects/cube.obj");
    Object ground("objects/ground.obj");

    Stack stack;

    Matrix C;
    C.SetPerspective(45.0, 6.2, 50);

    Matrix T;
    T.SetTranslate(0, -1.41, -9);
    C.Multiply(T);

    T.SetRotation(80, axis::kAxisX);
    C.Multiply(T);

    T.SetRotation(48, axis::kAxisZ);
    C.Multiply(T);

    T.SetScale(-1, -1, 1);
    C.Multiply(T);

    stack.Push(C);

    T.SetScale(-1, 1, 1);
    C.Multiply(T);

    frame.DrawObject(ground, C);

    T.SetTranslate(0, 0, 1);
    C.Multiply(T);

    T.SetRotation(-20, axis::kAxisZ);
    C.Multiply(T);

    frame.DrawObject(cube, C);

    C = stack.Pop();
    stack.Push(C);

    T.SetScale(0.3, 0.4, 0.5);
    C.Multiply(T);

    T.SetTranslate(-5, -3.8, 1);
    C.Multiply(T);

    frame.DrawObject(cube, C);
    */

    Tokenizer t("program.jbr", &frame);

    if (frame.WriteFrame()) {
        std::cout << "Frame written" << std::endl;
    }
    else {
        std::cout << "Error";
    }

    
}
