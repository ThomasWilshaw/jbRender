// jbRender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <OpenEXR/ImfInputFile.h>
#include <OpenEXR/ImfChannelList.h>
#include <OpenEXR/ImfFrameBuffer.h>
#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/half.h>
#include <cassert>

#include "frame.h"
#include "object.h"

using namespace Imf;
using namespace Imath;



int main()
{
    std::cout << "Hello World!\n";
    
    Frame frame(1920, 1080, Rgba(1.0, 1.0, 1.0, 1.0));
    

    Object square("objects/square_based_pyramid.obj");
    frame.DrawObject(square);

    if (frame.WriteFrame()) {
        std::cout << "Frame written";
    }
    else {
        std::cout << "Error";
    }
}
