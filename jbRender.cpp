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
    
    Frame frame(500, 500, Rgba(1.0, 1.0, 1.0, 1.0));
    

    Object square("objects/square.obj");
    frame.DrawObject(square);

    /*
    frame.MoveTo(0, 0);
    for (int i = 0; i < square.PolyCount(); i++) {
        for (int j = 0; j < square.Polys()[i].verts.size(); j++) {
            frame.DrawTo((square.Vert(i, j).x+1)*100, (square.Vert(i, j).y+1)*100);
        }
        frame.DrawTo((square.Vert(0, 0).x+1) * 100, (square.Vert(0, 0).y+1) * 100);
    }
    */

    if (frame.WriteFrame()) {
        std::cout << "Frame written";
    }
    else {
        std::cout << "Error";
    }
}
