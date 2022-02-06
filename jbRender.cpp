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
    C.SetPerspective(45.0, 6.2, 11.8);

    Matrix T;
    T.SetScale(5, 5, -1);
    C.Multiply(T);
    C.PrintMatrix();

    T.SetTranslate(0, -1.41, 9);
    C.Multiply(T);

    frame.DrawObject(pyramid, C);

    T.SetTranslate(2, 0, 0);
    C.Multiply(T);

    frame.DrawObject(pyramid, C);

    T.SetTranslate(2, 0, 0);
    C.Multiply(T);

    frame.DrawObject(cube, C);

    if (frame.WriteFrame()) {
        std::cout << "Frame written" << std::endl;
    }
    else {
        std::cout << "Error";
    }
    /*
    Matrix C;
    std::vector< std::vector<double> > c = { {2, 0, 0, 0}, {0, 2, 0, 0}, {0, 0, 2, 0}, {0, 0, 0, 2} };
    C.SetData(c);
    C.PrintMatrix();

    Matrix T;
    std::vector< std::vector<double> > t = { {3, 0, 0, 0}, {0, 3, 0, 0}, {0, 0, 3, 0}, {0, 0, 0, 3} };
    T.SetData(t);
    T.PrintMatrix();

    C.Multiply(T);
    C.PrintMatrix();
    */
}
