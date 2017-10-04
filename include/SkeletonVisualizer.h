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
        size_t IndicesSize = 0;
        GLint CameraUniformLocation;
        Camera Cam;

    public:
        SkeletonVisualizer() {
            AddKeyboardEvent(static_cast<char>(27), [this]() { CloseWindow(); });
            AddKeyboardEvent('w', [this]() { Cam.StepForward(); });
            AddKeyboardEvent('s', [this]() { Cam.StepBackward(); });
            AddKeyboardEvent(GLUT_KEY_UP, [this] { Cam.RotateTop(); });
            AddKeyboardEvent(GLUT_KEY_DOWN, [this] { Cam.RotateDown(); });
            AddKeyboardEvent(GLUT_KEY_LEFT, [this] { Cam.RotateLeft(); });
            AddKeyboardEvent(GLUT_KEY_RIGHT, [this] { Cam.RotateRight(); });
        }

        void Run() override;
        void RenderFunction() override;
    };

}

#endif //HORS_SKELETON_VISUALIZER_H
