#include <iostream>
#include <sstream>
#include <fstream>

#include "tokenizer.h"

#include "maths.h"
#include "object.h"

Tokenizer::Tokenizer(const std::string filename, Frame* frame):
    frame_(frame)
{
    C.SetIdentity();
    LoadObjects();

    Matrix T;
    T.SetIdentity();
    
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) {
        std::cout << "ERROR: Failed to open program file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash[5];

        if (!line.compare(0, 5, "PERS ")) {
            double theta, zn, zf = 0;
            char c;

            iss >> trash;

            iss >> theta >> c;
            iss >> zn >> c;
            iss >> zf >> c;

            T.SetPerspective(theta, zn, zf);
            C.Multiply(T);

        } else if (!line.compare(0, 5, "TRAN ")) {
            double x, y, z = 0;
            char c;

            iss >> trash;

            iss >> x >> c;
            iss >> y >> c;
            iss >> z >> c;

            T.SetTranslate(x, y, z);
            C.Multiply(T);

        } else if (!line.compare(0, 4, "ROT ")) {
            double angle = 0;
            int axis = 0;
            char c;

            iss >> trash;

            iss >> angle >> c;
            iss >> axis >> c;
            std::cout << angle << " " << axis << std::endl;
            if (axis == 1) {
                T.SetRotation(angle, axis::kAxisX);
            } else if (axis == 2){
                T.SetRotation(angle, axis::kAxisY);
            } else if (axis == 3) {
                T.SetRotation(angle, axis::kAxisZ);
            }
            C.Multiply(T);

        } else if (!line.compare(0, 5, "SCAL ")){
            double x, y, z = 0;
            char c;

            iss >> trash;

            iss >> x >> c;
            iss >> y >> c;
            iss >> z >> c;

            T.SetScale(x, y, z);
            C.Multiply(T);

        } else if (!line.compare(0, 5, "DRAW ")){
            std::string object;

            iss >> trash;
            iss >> object;
            
            DrawObject(object);

        } else if (!line.compare(0, 4, "PUSH")){
            stack_.Push(C);

        } else if (!line.compare(0, 3, "POP")){
            C = stack_.Pop();
        } else {
            std::cout << "ERROR: Invalid syntax: " << line << std::endl;
        }
    }
}

void Tokenizer::DrawObject(std::string obj)
{
    if (obj.compare(0, 6, "GPLANE") == 0) {
        frame_->DrawObject(obj_list_.at(2), C);
        return;
    }
    if (obj.compare(0, 4, "CUBE") == 0) {
        frame_->DrawObject(obj_list_.at(1), C);
        return;
    }
    if (obj.compare(0, 6, "PYRAMID") == 0) {
        frame_->DrawObject(obj_list_.at(0), C);
        return;
    }
}

void Tokenizer::LoadObjects()
{
    Object pyramid("objects/square_based_pyramid.obj");
    obj_list_.push_back(pyramid);

    Object cube("objects/cube.obj");
    obj_list_.push_back(cube);

    Object ground("objects/ground.obj");
    obj_list_.push_back(ground);
}
