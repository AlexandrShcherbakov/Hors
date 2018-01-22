//
// Created by alex on 09.01.18.
//

#include "SceneProperties.h"

#include <iostream>
#include <sstream>


namespace Hors {
    SceneProperties::SceneProperties(const std::string& path) {
        doc.load_file(path.c_str());
    }

    std::vector<glm::vec4> SceneProperties::GetDiffuseColors() const {
        std::vector<glm::vec4> colors;
        for(auto material: doc.child("COLLADA").child("library_materials").children("material")) {
            uint materialId = material.attribute("maxid").as_uint();
            if (materialId >= colors.size()) {
                colors.resize(static_cast<unsigned>(materialId + 1));
            }
            std::stringstream ss(material.child("hydra").child("diffuse").child("color").text().as_string());
            for (int i = 0; i < 3; ++i) {
                ss >> colors[materialId][i];
            }
            colors[materialId][3] = 1;
        }
        return colors;
    }
}