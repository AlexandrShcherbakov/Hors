//
// Created by alex on 05.10.17.
//

#ifndef HORS_SURFACEVISUALIZER_H
#define HORS_SURFACEVISUALIZER_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "HorsProgram.h"

namespace Hors {

    class SurfaceVisualizer : public Program {
    private:
        size_t IndicesSize;
    public:
        void Run() override;
        void RenderFunction() override;
    };

}

#endif //HORS_SURFACEVISUALIZER_H
