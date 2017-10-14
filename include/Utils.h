//
// Created by alex on 28.08.17.
//

#ifndef HORS_UTILS_H
#define HORS_UTILS_H

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>

#include "HydraExport.h"

#define CHECK_GL_ERRORS Hors::ThrowExceptionOnGLError(__LINE__,__FILE__);

namespace Hors {
    void ThrowExceptionOnGLError(int line, const char * file);

    GLuint ReadAndCompileShader(const std::string & path, GLenum shaderType);

    GLuint CompileShaderProgram(GLuint vertexShader, GLuint fragmentShader);

    template<GLenum Target, typename T>
    GLuint GenAndFillBuffer(const T* data, const size_t size) {
        GLuint buffer;
        glGenBuffers(1, &buffer); CHECK_GL_ERRORS;
        glBindBuffer(Target, buffer); CHECK_GL_ERRORS;
        glBufferData(Target, size * sizeof(T), data, GL_STATIC_DRAW); CHECK_GL_ERRORS;
        glBindBuffer(Target, 0); CHECK_GL_ERRORS;
        return buffer;
    }

    template<GLenum Target, typename T>
    GLuint GenAndFillBuffer(const std::vector<T>& data) {
        return GenAndFillBuffer<Target>(data.data(), data.size());
    }

    std::vector<glm::vec4> GetPointsByIndices(const HydraGeomData& data);

    std::vector<glm::vec4> GenRandomTrianglesColors(const HydraGeomData& data);

    std::vector<unsigned> GenerateRangeIndices(const HydraGeomData& data);

    std::vector<unsigned> GenEdgesIndices(const HydraGeomData& data);

    inline void SetUniformByLocation(const GLint location, const int value) {
        glUniform1i(location, value); CHECK_GL_ERRORS;
    }

    inline void SetUniformByLocation(const GLint location, const glm::mat4& value) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)); CHECK_GL_ERRORS;
    }

    template<typename T>
    void SetUniform(const GLuint program, const std::string& uniform, const T& value) {
        glUseProgram(program); CHECK_GL_ERRORS;
        GLint location = glGetUniformLocation(program, uniform.c_str()); CHECK_GL_ERRORS;
        if (location == -1) {
            std::cerr << "Uniform \"" << uniform << "\" not found!" << std::endl;
        }
        SetUniformByLocation(location, value);
    }
}

#endif //HORS_UTILS_H
