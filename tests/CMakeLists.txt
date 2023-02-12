include_directories(${CMAKE_SOURCE_DIR})

add_executable(face_vertex_compare face_vertex_compare.cpp ${CMAKE_SOURCE_DIR}/frame.cpp ${CMAKE_SOURCE_DIR}/maths.cpp ${CMAKE_SOURCE_DIR}/edge.cpp ${CMAKE_SOURCE_DIR}/polygon.cpp  ${CMAKE_SOURCE_DIR}/object.cpp ${CMAKE_SOURCE_DIR}/Scene.cpp ${CMAKE_SOURCE_DIR}/stack.cpp ${CMAKE_SOURCE_DIR}/tokenizer.cpp ${CMAKE_SOURCE_DIR}/renderer.cpp)
add_executable(edge_edge_compare edge_edge_compare.cpp ${CMAKE_SOURCE_DIR}/frame.cpp ${CMAKE_SOURCE_DIR}/maths.cpp ${CMAKE_SOURCE_DIR}/edge.cpp ${CMAKE_SOURCE_DIR}/polygon.cpp  ${CMAKE_SOURCE_DIR}/object.cpp ${CMAKE_SOURCE_DIR}/Scene.cpp ${CMAKE_SOURCE_DIR}/stack.cpp ${CMAKE_SOURCE_DIR}/tokenizer.cpp ${CMAKE_SOURCE_DIR}/renderer.cpp)

target_link_libraries (face_vertex_compare
    PUBLIC
        OpenEXR::OpenEXR
        Imath::Imath
        #Imath::Half
    )

target_link_libraries (edge_edge_compare
    PUBLIC
        OpenEXR::OpenEXR
        Imath::Imath
        #Imath::Half
    )

add_test(FaceVertexCompare face_vertex_compare)
add_test(EdgeEdgeCompare edge_edge_compare)