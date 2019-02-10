//
// Created by alex on 09.01.18.
//

#ifndef HORS_SCENEPROPERTIES_H
#define HORS_SCENEPROPERTIES_H

#include <string>
#include <vector>

#include <glm/vec4.hpp>
#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <pugixml-1.8/src/pugixml.hpp>

#include "Camera.h"

namespace Hors {

    class SpotLight {
        glm::vec3 Position;
        glm::vec3 Direction;
        glm::vec3 Color;
        float Multiplier;
        float OuterAngle;
        float InnerAngle;

    public:
        SpotLight(
            const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
            const float multiplier, const float outerAngle, const float innerAngle
        ):
            Position(position),
            Direction(direction),
            Color(color),
            Multiplier(multiplier),
            OuterAngle(outerAngle),
            InnerAngle(innerAngle)
        {}

        glm::vec3 GetPosition() const { return Position; }
        glm::vec3 GetDirection() const { return Direction; }
        glm::vec3 GetColor() const { return Color; }
        float GetMultiplier() const { return Multiplier; }
        float GetOuterAngle() const { return OuterAngle; }
        float GetInnerAngle() const { return InnerAngle; }

        glm::mat4 GenShiftMatrix(const glm::vec3& shift) const {
            glm::mat4 shiftMatrix(1);
            shiftMatrix[3] = glm::vec4(-shift, 1);
            return shiftMatrix;
        }

        glm::mat4 GetMatrix() const {
            return glm::perspective(glm::radians(OuterAngle + 10), 1.f, 0.001f, 100.f)
                   * glm::lookAt(Position, Position + Direction, glm::vec3(1, 0, 0));
        }
    };

    class SceneProperties {
        pugi::xml_document doc = {};
        std::vector<glm::vec4> GetMaterialComponent(const std::string& name) const;

    public:
        explicit SceneProperties(const std::string&);

        struct TextureRecordInfo {
            uint id;
            std::string location;
            uint offset;
            uint bytesize;
            uint width;
            uint height;
        };

        std::vector<glm::vec4> GetDiffuseColors() const;
        std::vector<glm::vec4> GetEmissionColors() const;
        std::vector<Camera> GetCameras(float screenRatio = 800.0f / 600) const;
        std::vector<SpotLight> GetLights() const;
        std::vector<glm::vec4> GetSpecularColors() const;
        std::vector<std::string> GetChunksPaths() const;
        std::vector<std::pair<glm::mat4, uint>> GetMeshMatrices() const;
        std::vector<TextureRecordInfo> GetTextures() const;
        std::vector<int> GetDiffuseTextures() const;
    };
}

#endif //HORS_SCENEPROPERTIES_H
