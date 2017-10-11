//
// Created by alex on 21.08.17.
//

#include "SurfaceVisualizer.h"

#include "DataGenerator.h"


int main(int argc, char ** argv) {
    GenerateTestData();
    Hors::RunProgram<Hors::SurfaceVisualizer>(argc, argv);
}