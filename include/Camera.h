//
// Created by alex on 28.08.17.
//

#ifndef HORS_CAMERA_H
#define HORS_CAMERA_H

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace Hors {

    class Camera {
    private:
        glm::vec3 Position = glm::vec3(0);
        glm::vec3 Direction = glm::vec3(0, 0, 1);
        glm::vec3 Up = glm::vec3(0, 1, 0);
        float FovY = 0;
        float ScreenRatio = 0;
        float ZNear = 0;
        float ZFar = 0;

    public:
        Camera() = default;

        Camera(
            const glm::vec3 position,
            const glm::vec3 direction,
            const glm::vec3 up,
            const float fovY,
            const float screenRatio,
            const float zNear,
            const float zFar
        ) :
        Position(position),
        Direction(direction),
        Up(up),
        FovY(fovY),
        ScreenRatio(screenRatio),
        ZNear(zNear),
        ZFar(zFar)
        {}

        glm::mat4 GetMatrix() const;

        glm::vec3 GetPosition() const {
            return Position;
        }

        void StepForward(const float length=0.1f) {
            Position += Direction * length;
        }

        void StepBackward(const float length=0.1f) {
            StepForward(-length);
        }

        void RotateTop(float angle=0.1f);

        void RotateDown(const float angle=0.1f) {
            RotateTop(-angle);
        }

        void RotateLeft(float angle=0.1f);

        void RotateRight(const float angle=0.1f) {
            RotateLeft(-angle);
        }
    };

}

#endif //HORS_CAMERA_H
