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
    

    Object square("objects/square_based_pyramid.obj");
    frame.DrawObject(square);

    if (frame.WriteFrame()) {
        std::cout << "Frame written" << std::endl;
    }
    else {
        std::cout << "Error";
    }

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

}
