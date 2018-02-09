//
// Created by alex on 31.01.18.
//

#ifndef HORS_MESH_H
#define HORS_MESH_H

#include <GL/glew.h>

#include <GLResourceWrappers.h>

struct HydraGeomData;

namespace Hors {

    class BaseMesh {
        GLBuffer PointsBuffer;
        GLBuffer NormalsBuffer;
        GLBuffer IndicesBuffer;
        GLuint IndicesCount = 0;
        GLVAO VAO;

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
