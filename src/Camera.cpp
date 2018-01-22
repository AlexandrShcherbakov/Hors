//
// Created by alex on 28.08.17.
//

#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

namespace Hors {
    glm::mat4 GenShiftMatrix(const glm::vec3& shift) {
        glm::mat4 shiftMatrix(1);
        shiftMatrix[3] = glm::vec4(-shift, 1);
        return shiftMatrix;
    }

    glm::mat4 Camera::GetMatrix() const {
        return glm::perspective(glm::radians(FovY), ScreenRatio, ZNear, ZFar)
            * glm::lookAt(Position, Position + Direction, Up)
            * GenShiftMatrix(Position);
    }

    void Camera::RotateLeft(const float angle) {
        glm::mat4 rot(1);
        rot[0][0] = rot[2][2] = cosf(angle);
        rot[0][2] = -sinf(angle);
        rot[2][0] = sinf(angle);
        Direction = glm::normalize(glm::vec3(rot * glm::vec4(Direction, 0)));
        Up = glm::normalize(glm::vec3(rot * glm::vec4(Up, 0)));
    }

    void Camera::RotateTop(const float angle) {

        const auto left = glm::cross(Up, Direction);
        const bool rotateUnderBottomBorder = angle < 0 && glm::dot(Direction, glm::vec3(0, -1, 0)) > 0.9f;
        const bool rotateAboveTopBorder = angle > 0 && glm::dot(Direction, glm::vec3(0, 1, 0)) > 0.9f;
        if (rotateAboveTopBorder || rotateUnderBottomBorder) {
            return;
        }
        Direction = glm::normalize(Direction * cosf(angle) + Up * sinf(angle));
        Up = glm::normalize(glm::cross(Direction, left));
    }
}