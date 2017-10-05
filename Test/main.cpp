//
// Created by alex on 21.08.17.
//

#include <iostream>

#include "../include/SurfaceVisualizer.h"
#include "../include/SimpleSceneData.h"


void GenerateSquare() {
    Hors::SimpleSceneData scene;
    std::vector<glm::tvec4<float> > points = {
            {-0.5, -0.5, 0, 1},
            {-0.5,  0.5, 0, 1},
            { 0.5,  0.5, 0, 1},
            { 0.5, -0.5, 0, 1}
    };
    scene.SetPoints(points.cbegin(), points.cend());
    std::vector<glm::tvec4<float> > normals = {4, {0, 0, 1, 0}};
    scene.SetNormals(normals.begin(), normals.end());
    std::vector<int> trianglesIndices = {
            0, 1, 3, 1, 2, 3
    };
    scene.SetTrianglesIndices(trianglesIndices.begin(), trianglesIndices.end());
    scene.SaveToFile("SimpleSquare.bin");
}

int main(int argc, char ** argv) {
    GenerateSquare();
    Hors::RunProgram<Hors::SurfaceVisualizer>(argc, argv);
}