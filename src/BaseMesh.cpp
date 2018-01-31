//
// Created by alex on 31.01.18.
//

#include "BaseMesh.h"

#include <map>
#include <vector>

#include <glm/vec4.hpp>

#include "HydraExport.h"
#include "Utils.h"

namespace Hors {

    void BaseMesh::Init(const HydraGeomData &scene) {
        std::vector<glm::vec4> points, normals;
        std::vector<uint> indices;
        IndicesCount = scene.getIndicesNumber();
        PointsBuffer = GenAndFillBuffer<GL_ARRAY_BUFFER>(
            scene.getVertexPositionsFloat4Array(),
            scene.getVerticesNumber() * 4
        );
        NormalsBuffer = GenAndFillBuffer<GL_ARRAY_BUFFER>(
            scene.getVertexNormalsFloat4Array(),
            scene.getVerticesNumber() * 4
        );
        IndicesBuffer = GenAndFillBuffer<GL_ELEMENT_ARRAY_BUFFER>(
            scene.getTriangleVertexIndicesArray(),
            scene.getIndicesNumber()
        );

        glGenVertexArrays(1, &VAO); CHECK_GL_ERRORS;
        glBindVertexArray(VAO); CHECK_GL_ERRORS;

        glBindBuffer(GL_ARRAY_BUFFER, PointsBuffer); CHECK_GL_ERRORS;
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr); CHECK_GL_ERRORS;
        glEnableVertexAttribArray(0); CHECK_GL_ERRORS;

        glBindBuffer(GL_ARRAY_BUFFER, NormalsBuffer); CHECK_GL_ERRORS;
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr); CHECK_GL_ERRORS;
        glEnableVertexAttribArray(1); CHECK_GL_ERRORS;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBuffer); CHECK_GL_ERRORS;
        glBindVertexArray(0); CHECK_GL_ERRORS;
    }

    void BaseMesh::Bind() const {
        glBindVertexArray(VAO); CHECK_GL_ERRORS;
    }

}