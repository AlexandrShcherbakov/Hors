//
// Created by alex on 27.08.17.
//

#ifndef HORS_SKELETON_VISUALIZER_H
#define HORS_SKELETON_VISUALIZER_H

#include <GL/glew.h>
#include "HorsProgram.h"

namespace Hors {

    class SkeletonVisualizer : public Program {
        size_t IndicesSize = 0;

    public:
        SkeletonVisualizer() {
            AddKeyboardEvent(static_cast<unsigned char>(27), [this]() { CloseWindow(); });
        }

        void Run() override;
        void RenderFunction() override;
    };

}

#endif //HORS_SKELETON_VISUALIZER_H
