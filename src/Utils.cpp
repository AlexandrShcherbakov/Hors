//
// Created by alex on 28.08.17.
//

#include <tuple>
#include <set>
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>

#include "GL/glew.h"

#include "Utils.h"

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

    GLuint CompileShader(const std::string &src, const GLenum shaderType) {
        GLuint shader = glCreateShader(shaderType);
        CHECK_GL_ERRORS;
        const char* src_c = src.c_str();
        const auto src_len = static_cast<GLint>(src.size());
        glShaderSource(shader, 1, &src_c, &src_len);
        CHECK_GL_ERRORS;
        glCompileShader(shader);
        CHECK_GL_ERRORS;

        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        CHECK_GL_ERRORS;
        if (success == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength); CHECK_GL_ERRORS;
            std::vector<char> errorLog(static_cast<unsigned>(maxLength));
            glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog.data()); CHECK_GL_ERRORS;
            glDeleteShader(shader); CHECK_GL_ERRORS;
            std::cerr << errorLog.data() << std::endl;
            std::cerr << std::endl << src << std::endl;
            exit(1);
        }

        return shader;
    }


    GLuint ReadAndCompileShader(const std::string & path, const GLenum shaderType) {
        std::ifstream in(path);
        std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        return CompileShader(src, shaderType);
    }


    GLuint CompileShaderProgram(const GLuint vertexShader, const GLuint fragmentShader) {
        GLuint program = glCreateProgram(); CHECK_GL_ERRORS;
        glAttachShader(program, vertexShader); CHECK_GL_ERRORS;
        glAttachShader(program, fragmentShader); CHECK_GL_ERRORS;
        glLinkProgram(program); CHECK_GL_ERRORS;

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked); CHECK_GL_ERRORS;
        if(isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength); CHECK_GL_ERRORS;
            std::vector<char> infoLog(static_cast<unsigned>(maxLength));
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data()); CHECK_GL_ERRORS;

            glDeleteProgram(program); CHECK_GL_ERRORS;
            glDeleteShader(vertexShader); CHECK_GL_ERRORS;
            glDeleteShader(fragmentShader); CHECK_GL_ERRORS;

            std::cerr << infoLog.data() << std::endl;
            exit(1);
        }

        return program;
    }

    std::vector<glm::vec4> GetPointsByIndices(const HydraGeomData& data) {
        std::vector<glm::vec4> points(data.getIndicesNumber());
        for (unsigned i = 0; i < points.size(); ++i) {
            unsigned index = data.getTriangleVertexIndicesArray()[i];
            const int COMPONENTS = 4;
            for (int j = 0; j < COMPONENTS; ++j) {
                points[i][j] = data.getVertexPositionsFloat4Array()[4 * index + j];
            }
        }
        return points;
    }

    std::vector<unsigned> GenerateRangeIndices(const HydraGeomData& data) {
        std::vector<unsigned> indices(data.getIndicesNumber());
        for (unsigned i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }
        return indices;
    }

    std::vector<glm::vec4> GenRandomTrianglesColors(const HydraGeomData& data) {
        std::vector<glm::vec4> colors(data.getIndicesNumber());
        std::default_random_engine engine;
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        for (unsigned i = 0; i < colors.size(); i += 3) {
            colors[i] = colors[i + 1] = colors[i + 2] = glm::vec4(dist(engine), dist(engine), dist(engine), 1);
        }
        return colors;
    }

    std::vector<unsigned> GenEdgesIndices(const HydraGeomData& data) {
        std::vector<unsigned> indices;
        const unsigned SIDES = 3u;
        for (unsigned i = 0; i < data.getIndicesNumber(); i += SIDES) {
            for (unsigned j = 0; j < SIDES; ++j) {
                indices.push_back(data.getTriangleVertexIndicesArray()[i + j]);
                indices.push_back(data.getTriangleVertexIndicesArray()[i + (j + 1) % SIDES]);
            }
        }
        return indices;
    }

    glm::vec3 ReadVec3(const std::string& s) {
        glm::vec3 result;
        std::stringstream ss(s);
        for (int i = 0; i < 3; ++i) {
            ss >> result[i];
        }
        return result;
    }
}