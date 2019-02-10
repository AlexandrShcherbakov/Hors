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

    std::vector<glm::vec4> SceneProperties::GetMaterialComponent(const std::string& name) const {
        std::vector<glm::vec4> colors;
        for(auto & material: doc.child("materials_lib").children("material")) {
            uint materialId = material.attribute("id").as_uint();
            if (materialId >= colors.size()) {
                colors.resize(static_cast<unsigned>(materialId + 1));
            }
            auto componentChild = material.child(name.c_str());
            if (componentChild) {
                colors[materialId] = glm::vec4(
                    ReadVec3(componentChild.child("color").attribute("val").as_string()), 1);
            } else {
                colors[materialId] = glm::vec4(0, 0, 0, 1);
            }
        }
        return colors;
    }

    std::vector<glm::vec4> SceneProperties::GetDiffuseColors() const {
        return GetMaterialComponent("diffuse");
    }

    std::vector<glm::vec4> SceneProperties::GetEmissionColors() const {
        return GetMaterialComponent("emission");
    }

    std::vector<Camera> SceneProperties::GetCameras(const float screenRatio) const {
        std::vector<Camera> cameras;
        for (auto & cameraNode: doc.child("cam_lib").children("camera")) {
            const glm::vec3 position = ReadVec3(cameraNode.child("position").text().as_string());
            const glm::vec3 direction = ReadVec3(cameraNode.child("look_at").text().as_string()) - position;
            const glm::vec3 up = ReadVec3(cameraNode.child("up").text().as_string());
            const float fovY = cameraNode.child("fov").text().as_float();
            const float zNear = cameraNode.child("nearClipPlane").text().as_float();
            const float zFar = cameraNode.child("farClipPlane").text().as_float();
            cameras.emplace_back(Camera(
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
        for (auto & lightNode: doc.child("lights_lib").children("light")) {
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

    std::vector<glm::vec4> SceneProperties::GetSpecularColors() const {
        return GetMaterialComponent("specular");
    }

    std::vector<std::string> SceneProperties::GetChunksPaths() const {
        std::vector<std::string> paths;
        for(auto & mesh: doc.child("geometry_lib").children("mesh")) {
            paths.emplace_back(mesh.attribute("loc").as_string());
        }
        return paths;
    }

    std::vector<std::pair<glm::mat4, uint>> SceneProperties::GetMeshMatrices() const {
        std::vector<std::pair<glm::mat4, uint>> result;
        for (auto & instance: doc.child("scenes").child("scene").children("instance")) {
            auto meshIdStr = instance.attribute("mesh_id");
            const auto idStr = instance.attribute("id");
            if (meshIdStr == nullptr) {
                continue;
            }
            const uint id = idStr.as_uint();
            if (id >= result.size()) {
                result.resize(id + 1);
            }
            const uint meshId = meshIdStr.as_uint();
            result[id] = std::make_pair(ReadMat4(instance.attribute("matrix").as_string()), meshId);
        }
        return result;
    }

    std::vector<SceneProperties::TextureRecordInfo> SceneProperties::GetTextures() const {
        std::vector<SceneProperties::TextureRecordInfo> records;
        for (const auto& record : doc.child("textures_lib").children("texture")) {
            TextureRecordInfo rec = {
                record.attribute("id").as_uint(),
                std::string(record.attribute("loc").as_string()),
                record.attribute("offset").as_uint(),
                record.attribute("bytesize").as_uint(),
                record.attribute("width").as_uint(),
                record.attribute("height").as_uint()
            };
            records.emplace_back(rec);
        }
        return records;
    }

    std::vector<int> SceneProperties::GetDiffuseTextures() const {
        std::vector<int> ids;
        for(auto & material: doc.child("materials_lib").children("material")) {
            uint materialId = material.attribute("id").as_uint();
            if (materialId >= ids.size()) {
                ids.resize(static_cast<unsigned>(materialId + 1));
            }
            auto componentChild = material.child("diffuse").child("color").child("texture");
            if (componentChild) {
                ids[materialId] = componentChild.attribute("id").as_int();
            } else {
                ids[materialId] = -1;
            }
        }
        return ids;
    }
}