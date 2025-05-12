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
        std::cout << "ERROR: Failed to open object file:" << filename << std::endl;
        return;
    }

    std::string line;

    // Count how many vertices and polygons we have
    int vertex_count = 0;
    int polygon_count = 0;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());

        if (!line.compare(0, 2, "v ")) {
            vertex_count++;
            continue;
        }
        if (!line.compare(0, 2, "f ")) {
            polygon_count++;
            continue;
        }
    }
    // Reset file back to the begining
    in.clear();
    in.seekg(0, std::ios::beg);

    verts_.x.resize(vertex_count);
    verts_.y.resize(vertex_count);
    verts_.z.resize(vertex_count);
    verts_.w.resize(vertex_count);

    polys_.resize(polygon_count);

    // Fill arrays
    vertex_count = 0;
    polygon_count = 0;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;

        if (!line.compare(0, 2, "v ")) { // verts
            iss >> trash;
            double x, y, z = 0.0;
            iss >> x;
            iss >> y;
            iss >>z;
            verts_.x[vertex_count] = x;
            verts_.y[vertex_count] = y;
            verts_.z[vertex_count] = z;
            verts_.w[vertex_count] = 1.0;
            vertex_count++;
        } else if (!line.compare(0, 2, "f ")) { // faces
            iss >> trash;
            int v;
            polygon p;
            while (iss >> v) {
                // obj files store vertices from 1 .. n
                p.vertices.push_back(v-1);
            }
            p.cull = false;
            p.wire = false;
            p.object_offset = -1;
            polys_[polygon_count] = p;
            polygon_count++;
        }
    }

    in.close();
}

int Object::PolyCount()
{
    return polys_.size();
}

vec3 Object::Vertex(int polygon, int vert)
{
    int vertex = polys_[polygon].vertices[vert];

    vec3 out;
    out.x = verts_.x[vertex];
    out.y = verts_.y[vertex];
    out.z = verts_.z[vertex];

    return out;
}

void Object::PrintVerts()
{
    std::cout << "---VERTS---" << std::endl;
    for (int i = 0; i < verts_.x.size(); i++) {
        std::cout << i << ": ";
        std::cout << verts_.x[i] << ", ";
        std::cout << verts_.y[i] << ", ";
        std::cout << verts_.z[i] << std::endl;
    }
}

void Object::PrintPolys()
{
    std::cout << "---POLYS---" << std::endl;

    for (int i = 0; i < polys_.size(); i++) {
        std::cout << i << ": ";
        for (int j = 0; j < polys_[i].vertices.size(); j++) {
            std::cout << polys_[i].vertices[i] << " ";
        }
    }
}