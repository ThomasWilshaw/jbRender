#include <iostream>
#include <sstream>
#include <fstream>

#include "object.h"
//https://www.andrewnoske.com/wiki/OBJ_file_format#Example_1a:_A_square_facing_forwards
//https://github.com/ssloy/tinyrenderer/blob/master/model.cpp

Object::Object(const std::string filename)
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) {
        std::cout << "ERROR: Failed to open " << filename;
        return;
    }

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;

        if (!line.compare(0, 2, "v ")) { // verts
            iss >> trash;
            vec3 v;
            iss >> v.x;
            iss >> v.y;
            iss >> v.z;
            verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) { // faces
            iss >> trash;
            int v;
            poly p;
            while (iss >> v) {
                p.verts.push_back(v-1);
            }
            p.vert_count = p.verts.size();
            polys_.push_back(p);
        }
    }

    in.close();
}

int Object::PolyCount()
{
    return polys_.size();
}

std::vector<poly> Object::Polys()
{
    return polys_;
}

void Object::PrintVerts()
{
    std::cout << "---VERTS---" << std::endl;
    for (int i = 0; i < verts_.size(); i++) {
        std::cout << i << ": ";
        std::cout << verts_[i].x << ", ";
        std::cout << verts_[i].y << ", ";
        std::cout << verts_[i].z << std::endl;
    }
}

void Object::PrintPolys()
{
    std::cout << "---POLYS---" << std::endl;

    for (int i = 0; i < polys_.size(); i++) {
        std::cout << i << ": ";
        for (int j = 0; j < polys_[i].verts.size(); j++) {
            std::cout << polys_[i].verts[j] << " ";
        }
    }
}