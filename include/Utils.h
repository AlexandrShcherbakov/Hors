//
// Created by alex on 28.08.17.
//

#ifndef HORS_UTILS_H
#define HORS_UTILS_H

#include <vector>

#include "glm/vec4.hpp"

#include "HydraExport.h"

#define CHECK_GL_ERRORS Hors::ThrowExceptionOnGLError(__LINE__,__FILE__);

namespace Hors {
    void ThrowExceptionOnGLError(int line, const char * file);

    GLuint ReadAndCompileShader(const std::string & path, const GLenum shaderType);

    GLuint CompileShaderProgram(const GLuint vertexShader, const GLuint fragmentShader);

    template<GLenum Target, typename T>
    GLuint GenAndFillBuffer(const std::vector<T>& data) {
        GLuint buffer;
        glGenBuffers(1, &buffer); CHECK_GL_ERRORS;
        glBindBuffer(Target, buffer); CHECK_GL_ERRORS;
        glBufferData(Target, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS;
        glBindBuffer(Target, 0); CHECK_GL_ERRORS;
        return buffer;
    }

    std::vector<glm::vec4> GetPointsByIndices(const HydraGeomData& data);

    std::vector<unsigned> GenerateRangeIndices(const HydraGeomData& data);

    std::vector<glm::vec4> GenRandomTrianglesColors(const HydraGeomData& data);

    std::vector<glm::vec4> ExtractPoints(const HydraGeomData& data);

    std::vector<unsigned> GenEdgesIndices(const HydraGeomData& data);
}

#endif //HORS_UTILS_H
