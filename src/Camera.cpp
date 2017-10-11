//
// Created by alex on 28.08.17.
//

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

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
}