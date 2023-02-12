cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(jbRender)

find_package(Imath CONFIG)
find_package(OpenEXR CONFIG)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(jbRender jbRender.cpp frame.cpp maths.cpp edge.cpp polygon.cpp object.cpp Scene.cpp stack.cpp tokenizer.cpp renderer.cpp)

target_link_libraries (jbRender
    PUBLIC
        OpenEXR::OpenEXR
        Imath::Imath
        #Imath::Half
    )

enable_testing()
add_subdirectory(tests)
