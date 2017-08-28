//
// Created by alex on 21.08.17.
//

#include <iostream>

#include "../include/SkeletonVisualizer.h"
#include "../include/SimpleSceneData.h"

class TestProgram : public Hors::Program {
public:
    TestProgram() {
        AddKeyboardEvent(static_cast<unsigned char>(27), []() {exit(0);});
        AddInitialFunction([]() {std::cout << "Initial function works" << std::endl; });
    }
    virtual void Run() {
        std::cout << "Run test program" << std::endl;
    }
    virtual void RenderFunction() {

    }
};

void GenerateSquare() {
    Hors::SimpleSceneData scene;
    std::vector<glm::tvec4<float> > points = {
            {-1, -1, 0, 0},
            {-1,  1, 0, 0},
            { 1,  1, 0, 0},
            { 1, -1, 0, 0}
    };
    scene.SetPoints(points.cbegin(), points.cend());
    std::vector<glm::tvec4<float> > normals = {4, {0, 0, 1, 0}};
    scene.SetNormals(normals.begin(), normals.end());
    std::vector<int> trianglesIndices = {
            0, 1, 3, 1, 2, 3
    };
    scene.SetTrianlesIndices(trianglesIndices.begin(), trianglesIndices.end());
    scene.SaveToFile("SimpleSquare.bin");
}

int main(int argc, char ** argv) {
    GenerateSquare();
    Hors::RunProgram<TestProgram>(argc, argv);
    //Hors::RunProgram<Hors::SkeletonVisualizer>(argc, argv);
}