//
// Created by alex on 21.08.17.
//

#include "../include/SurfaceVisualizer.h"

#include "DataGenerator.h"


int main(int argc, char ** argv) {
    GeneateTestData();
    Hors::RunProgram<Hors::SurfaceVisualizer>(argc, argv);
}