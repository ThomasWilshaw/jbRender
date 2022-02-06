// jbRender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "frame.h"
#include "maths.h"
#include "object.h"

using namespace Imf;
using namespace Imath;



int main()
{
    Frame frame(1920, 1080, Rgba(1.0, 1.0, 1.0, 1.0));
    

    Object pyramid("objects/square_based_pyramid.obj");
    Object cube("objects/cube.obj");
    Matrix C;
    C.SetPerspective(45.0, 6.2, 50);

    Matrix T;
    T.SetTranslate(0, -1.41, -15);
    C.Multiply(T);

    T.SetRotation(-20, axis::kAxisY);
    C.Multiply(T);

    T.SetScale(3, 3, 3);
    C.Multiply(T);

    frame.DrawObject(cube, C);


    if (frame.WriteFrame()) {
        std::cout << "Frame written" << std::endl;
    }
    else {
        std::cout << "Error";
    }
}
