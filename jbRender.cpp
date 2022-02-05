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

using namespace Imf;
using namespace Imath;



int main()
{
    std::cout << "Hello World!\n";
    
    Frame frame(500, 500, Rgba(1.0, 1.0, 1.0, 1.0));

    frame.DrawLine(50, 50, 450, 50);
    frame.DrawLine(50, 50, 450, 70);
    frame.DrawLine(50, 50, 450, 100);
    frame.DrawLine(50, 50, 450, 150);
    frame.DrawLine(50, 50, 450, 200);

    if (frame.WriteFrame()) {
        std::cout << "Frame written";
    }
    else {
        std::cout << "Error";
    }
}
