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

    class SceneProperties {
        pugi::xml_document doc;
    public:
        SceneProperties(const std::string&);

        std::vector<glm::vec4> GetDiffuseColors() const;
        std::vector<Camera> GetCameras(float screenRatio = 800.0f / 600) const;
    };

}

#endif //HORS_SCENEPROPERTIES_H
