//
// Created by alex on 28.08.17.
//

#include <iostream>
#include <sstream>

#include "GL/glew.h"

namespace Hors {

    void ThrowExceptionOnGLError(const int line, const char * file) {
        const GLenum glError = glGetError();

        if(glError == GL_NO_ERROR)
            return;

        std::stringstream buffer;
        switch(glError) {
            case GL_INVALID_ENUM:
                buffer << "GL_INVALID_ENUM file " << file << " line " << line << std::endl;
                break;

            case GL_INVALID_VALUE:
                buffer << "GL_INVALID_VALUE file " << file << " line " << line << std::endl;
                break;

            case GL_INVALID_OPERATION:
                buffer << "GL_INVALID_OPERATION file " << file << " line " << line << std::endl;
                break;

            case GL_STACK_OVERFLOW:
                buffer << "GL_STACK_OVERFLOW file " << file << " line " << line << std::endl;
                break;

            case GL_STACK_UNDERFLOW:
                buffer << "GL_STACK_UNDERFLOW file " << file << " line " << line << std::endl;
                break;

            case GL_OUT_OF_MEMORY:
                buffer << "GL_OUT_OF_MEMORY file " << file << " line " << line << std::endl;
                break;

            default:
                buffer.unsetf(std::ios::dec);
                buffer.setf(std::ios::oct);
                buffer << "Unknown error 0x" << glError << " file " << file;
                buffer.unsetf(std::ios::oct);
                buffer.setf(std::ios::dec);
                buffer << " line " << line << std::endl;
                break;
        }

        std::cerr << "OpenGL error!" << std::endl << buffer.str();
        exit(1);
    }
}