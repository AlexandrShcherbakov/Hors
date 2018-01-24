//
// Created by alex on 09.01.18.
//

#ifndef HORS_SCENEPROPERTIES_H
#define HORS_SCENEPROPERTIES_H

#include <string>
#include <vector>

#include <glm/vec4.hpp>
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
    };

    class SceneProperties {
        pugi::xml_document doc;
    public:
        SceneProperties(const std::string&);

        std::vector<glm::vec4> GetDiffuseColors() const;
        std::vector<Camera> GetCameras(float screenRatio = 800.0f / 600) const;
        std::vector<SpotLight> GetLights() const;
    };
}

#endif //HORS_SCENEPROPERTIES_H
