//
// Created by alex on 07.10.17.
//

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "HydraExport.h"


void GenerateSquare() {
    std::vector<glm::vec4> points = {
        {-0.5, -0.5, 0, 1},
        {-0.5,  0.5, 0, 1},
        { 0.5,  0.5, 0, 1},
        { 0.5, -0.5, 0, 1}
    };
    std::vector<glm::vec4> normals = {4, {0, 0, 1, 0}};
    std::vector<glm::vec2> texCoordinates = {4, {0, 0}};
    std::vector<uint32> trianglesIndices = {
        0, 1, 3, 1, 2, 3
    };
    std::vector<uint32> materialNumbers(2, 0);
    HydraGeomData scene;
    scene.setData(
        static_cast<uint32>(points.size()),
        reinterpret_cast<float*>(points.data()),
        reinterpret_cast<float*>(normals.data()),
        nullptr,
        reinterpret_cast<float*>(texCoordinates.data()),
        static_cast<uint32>(trianglesIndices.size()),
        trianglesIndices.data(),
        materialNumbers.data()
    );
    scene.write("SimpleSquare.bin");
}

void GenerateTestData() {
    GenerateSquare();
}