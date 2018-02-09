//
// Created by alex on 02.02.18.
//

#ifndef HORS_GLRESOURCEWRAPPERS_H
#define HORS_GLRESOURCEWRAPPERS_H

#include <memory>

#include <GL/glew.h>

#define CHECK_GL_ERRORS Hors::ThrowExceptionOnGLError(__LINE__,__FILE__);

namespace Hors {

    void ThrowExceptionOnGLError(int line, const char * file);

    using GLBuffer = std::shared_ptr<GLuint>;
    inline GLBuffer MakeGLBuffer() {
        auto buffer = std::shared_ptr<GLuint>(new GLuint, [](GLuint * p) {
            glDeleteBuffers(1, p); CHECK_GL_ERRORS;
            delete p;
        });
        glGenBuffers(1, buffer.get()); CHECK_GL_ERRORS;
        return buffer;
    }

    using GLVAO = std::shared_ptr<GLuint>;
    inline GLVAO MakeGLVAO() {
        auto vao = std::shared_ptr<GLuint>(new GLuint, [](GLuint * p) {
            glDeleteVertexArrays(1, p); CHECK_GL_ERRORS;
            delete p;
        });
        glGenVertexArrays(1, vao.get()); CHECK_GL_ERRORS;
        return vao;
    }

    using GLProgram = std::shared_ptr<GLuint>;
    inline GLProgram MakeGLProgram() {
        auto prog = std::shared_ptr<GLuint>(new GLuint, [](const GLuint * p) {
            glDeleteProgram(*p); CHECK_GL_ERRORS;
            delete p;
        });
        *prog = glCreateProgram(); CHECK_GL_ERRORS;
        return prog;
    }
}

#endif //HORS_GLRESOURCEWRAPPERS_H
