//
// Created by alex on 05.10.17.
//

#ifndef HORS_SURFACE_VISUALIZER_H
#define HORS_SURFACE_VISUALIZER_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "HorsProgram.h"

namespace Hors {

    class SurfaceVisualizer : public Program {
    private:
        size_t RunSize;
    public:
        void Run() override;
        void RenderFunction() override;
    };

}

#endif //HORS_SURFACE_VISUALIZER_H
