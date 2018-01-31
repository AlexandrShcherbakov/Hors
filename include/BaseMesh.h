//
// Created by alex on 31.01.18.
//

#ifndef HORS_MESH_H
#define HORS_MESH_H

#include <GL/glew.h>


struct HydraGeomData;

namespace Hors {

    class BaseMesh {
        GLuint PointsBuffer = 0;
        GLuint NormalsBuffer = 0;
        GLuint IndicesBuffer = 0;
        GLuint IndicesCount = 0;
        GLuint VAO = 0;

    public:
        BaseMesh() = default;
        void Init(const HydraGeomData & scene);
        void Bind() const;
        GLuint GetIndicesCount() const {
            return IndicesCount;
        }
    };

}

#endif //HORS_MESH_H
