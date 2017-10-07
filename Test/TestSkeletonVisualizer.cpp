//
// Created by alex on 07.10.17.
//

#include "../include/SkeletonVisualizer.h"

#include "DataGenerator.h"


int main(int argc, char ** argv) {
    GeneateTestData();
    Hors::RunProgram<Hors::SkeletonVisualizer>(argc, argv);
}