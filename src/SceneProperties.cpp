//
// Created by alex on 09.01.18.
//

#include "SceneProperties.h"

#include <iostream>
#include <sstream>

#include "Utils.h"


namespace Hors {
    SceneProperties::SceneProperties(const std::string& path) {
        doc.load_file(path.c_str());
    }

    std::vector<glm::vec4> SceneProperties::GetDiffuseColors() const {
        std::vector<glm::vec4> colors;
        for(auto & material: doc.child("COLLADA").child("library_materials").children("material")) {
            uint materialId = material.attribute("maxid").as_uint();
            if (materialId >= colors.size()) {
                colors.resize(static_cast<unsigned>(materialId + 1));
            }
            colors[materialId] = glm::vec4(
                ReadVec3(material.child("hydra").child("diffuse").child("color").text().as_string()), 1);
        }
        return colors;
    }

    std::vector<Camera> SceneProperties::GetCameras(const float screenRatio) const {
        std::vector<Camera> cameras;
        for (auto & cameraNode: doc.child("COLLADA").child("library_cameras").children("camera")) {
            const glm::vec3 position = ReadVec3(cameraNode.child("position").text().as_string());
            const glm::vec3 direction = ReadVec3(cameraNode.child("look_at").text().as_string()) - position;
            const glm::vec3 up = ReadVec3(cameraNode.child("up").text().as_string());
            const float fovY = cameraNode.child("fov").text().as_float();
            const float zNear = cameraNode.child("nearClipPlane").text().as_float();
            const float zFar = cameraNode.child("farClipPlane").text().as_float();
            cameras.push_back(Camera(
                position,
                direction,
                up,
                fovY,
                screenRatio,
                zNear,
                zFar
            ));
        }
        return cameras;
    }

    std::vector<SpotLight> SceneProperties::GetLights() const {
        std::vector<SpotLight> lights;
        for (auto & lightNode: doc.child("COLLADA").child("library_lights").children("light")) {
            if (lightNode.attribute("type").as_string() != std::string("Spot")) {
                continue;
            }
            lights.emplace_back(SpotLight(
                ReadVec3(lightNode.child("position").text().as_string()),
                ReadVec3(lightNode.child("direction").text().as_string()),
                ReadVec3(lightNode.child("intensity").child("color").text().as_string()),
                lightNode.child("intensity").child("multiplier").text().as_float(),
                lightNode.child("falloff_angle").text().as_float(),
                lightNode.child("falloff_angle2").text().as_float()
            ));
        }
        return lights;
    }
}