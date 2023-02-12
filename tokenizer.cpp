#include <iostream>
#include <sstream>
#include <fstream>

#include "tokenizer.h"

#include "maths.h"
#include "object.h"

Tokenizer::Tokenizer(const std::string filename, Scene* scene, Renderer* renderer):
    scene_(scene),
    renderer_(renderer)
{
    C = new Matrix();
    C->SetIdentity();
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

        if (!line.compare(0, 1, "#")) {
            continue;
        }

        if (!line.compare(0, 2, "/*")) {
            while (!in.eof()){
                std::getline(in, line);
                std::istringstream itt(line.c_str());

                if (!line.compare(0, 2, "*/")) {
                    break;
                }
            }
            continue;
        }

        if (!line.compare(0, 4, "WIRE")) {
            renderer_->SetWireFrameMode(true);
            continue;
        }

        if (!line.compare(0, 5, "PERS ")) {
            double theta, zn, zf = 0;
            char c;

            iss >> trash;

            iss >> theta >> c;
            iss >> zn >> c;
            iss >> zf >> c;

            T.SetPerspective(theta, zn, zf);
            C->Multiply(T);

        } else if (!line.compare(0, 5, "TRAN ")) {
            double x, y, z = 0;
            char c;

            iss >> trash;

            iss >> x >> c;
            iss >> y >> c;
            iss >> z >> c;

            T.SetTranslate(x, y, z);
            C->Multiply(T);

        } else if (!line.compare(0, 4, "ROT ")) {
            double angle = 0;
            int axis = 0;
            char c;

            iss >> trash;

            iss >> angle >> c;
            iss >> axis >> c;
            //std::cout << angle << " " << axis << std::endl;
            if (axis == 1) {
                T.SetRotation(angle, axis::kAxisX);
            } else if (axis == 2){
                T.SetRotation(angle, axis::kAxisY);
            } else if (axis == 3) {
                T.SetRotation(angle, axis::kAxisZ);
            }
            C->Multiply(T);

        } else if (!line.compare(0, 5, "SCAL ")){
            double x, y, z = 0;
            char c;

            iss >> trash;

            iss >> x >> c;
            iss >> y >> c;
            iss >> z >> c;

            T.SetScale(x, y, z);
            C->Multiply(T);

        } else if (!line.compare(0, 5, "DRAW ")){
            std::string object_name;

            iss >> trash;
            iss >> object_name;

            scene_->AddObject(GetObjectFromName(object_name), C);

        } else if (!line.compare(0, 4, "PUSH")){
            stack_.Push(*C);

        }
        else if (!line.compare(0, 3, "POP")) {
            C->SetData(stack_.Pop().data());
        }else if(!line.compare(0, 4, "PRMT")) {
            C->PrintMatrix();
        } else {
            std::cout << "ERROR: Invalid syntax: " << line << std::endl;
        }
    }

   // frame_->DrawScene(scene_);
}

Object* Tokenizer::GetObjectFromName(std::string obj)
{
    if (obj.compare(0, 6, "B_CUBE") == 0) {
        return obj_list_.at(6);
    }
    if (obj.compare(0, 6, "SPHERE") == 0) {
        return obj_list_.at(5);
    }
    if (obj.compare(0, 6, "MONKEY") == 0) {
        return obj_list_.at(4);
    }
    if (obj.compare(0, 6, "SQUARE") == 0) {
        return obj_list_.at(3);
    }
    if (obj.compare(0, 6, "GPLANE") == 0) {
        return obj_list_.at(2);
    }
    if (obj.compare(0, 4, "CUBE") == 0) {
        return obj_list_.at(1);
    }
    if (obj.compare(0, 7, "PYRAMID") == 0) {
        return obj_list_.at(0);
    }
}

void Tokenizer::LoadObjects()
{
    Object* pyramid = new Object("..\\..\\..\\objects\\square_based_pyramid.obj");
    obj_list_.push_back(pyramid);

    Object* cube = new Object("..\\..\\..\\objects\\cube.obj");
    obj_list_.push_back(cube);

    Object* ground = new Object("..\\..\\..\\objects\\ground.obj");
    obj_list_.push_back(ground);

    Object* square = new Object("..\\..\\..\\objects\\square.obj");
    obj_list_.push_back(square);

    Object* monkey = new Object("..\\..\\..\\objects\\monkey.obj");
    obj_list_.push_back(monkey);

    Object* sphere = new Object("..\\..\\..\\objects\\sphere.obj");
    obj_list_.push_back(sphere);

    Object* b_cube = new Object("..\\..\\..\\objects\\extrude_cube.obj");
    obj_list_.push_back(b_cube);
}
