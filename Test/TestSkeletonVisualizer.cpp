//
// Created by alex on 07.10.17.
//

#include "SkeletonVisualizer.h"

#include "DataGenerator.h"


int main(int argc, char ** argv) {
    GenerateTestData();
    Hors::RunProgram<Hors::SkeletonVisualizer>(argc, argv);
}