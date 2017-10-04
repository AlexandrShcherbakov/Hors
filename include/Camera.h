//
// Created by alex on 28.08.17.
//

#ifndef HORS_CAMERA_H
#define HORS_CAMERA_H

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/geometric.hpp"

namespace Hors {

    class Camera {
    private:
        glm::vec3 Position;
        glm::vec3 Direction;
        glm::vec3 Up;
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

        void StepForward(const float length=0.1f) {
            Position += Direction * length;
        }

        void StepBackward(const float length=0.1f) {
            StepForward(-length);
        }

        void RotateTop(const float angle=0.1f) {
            glm::vec3 left = glm::cross(Up, Direction);
            Direction = glm::normalize(Direction * cosf(angle) + Up * sinf(angle));
            Up = glm::normalize(glm::cross(Direction, left));
        }

        void RotateDown(const float angle=0.1f) {
            RotateTop(-angle);
        }

        void RotateLeft(const float angle=0.1f) {
            Direction = glm::normalize(
                Direction * cosf(angle)
                + glm::normalize(glm::cross(Up, Direction)) * sinf(angle)
            );
        }

        void RotateRight(const float angle=0.1f) {
            RotateLeft(-angle);
        }
    };

}

#endif //HORS_CAMERA_H
