//
// Created by alex on 27.08.17.
//

#ifndef HORS_SKELETON_VISUALIZER_H
#define HORS_SKELETON_VISUALIZER_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Camera.h"
#include "HorsProgram.h"

namespace Hors {

    class SkeletonVisualizer : public Program {
        size_t RunSize;

    public:
        void Run() override;
        void RenderFunction() override;
    };

}

#endif //HORS_SKELETON_VISUALIZER_H
