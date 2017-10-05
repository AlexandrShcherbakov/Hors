//
// Created by alex on 28.08.17.
//

#ifndef HORS_UTILS_H
#define HORS_UTILS_H

#define CHECK_GL_ERRORS Hors::ThrowExceptionOnGLError(__LINE__,__FILE__);

namespace Hors {
    void ThrowExceptionOnGLError(int line, const char * file);

    GLuint ReadAndCompileShader(const std::string & path, const GLenum shaderType);

    GLuint CompileShaderProgram(const GLuint vertexShader, const GLuint fragmentShader);
}

#endif //HORS_UTILS_H
