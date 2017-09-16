//
// Created by alex on 27.08.17.
//

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "../include/SimpleSceneData.h"
#include "../include/SkeletonVisualizer.h"
#include "../include/Utils.h"

namespace Hors {

    GLuint ReadAndCompileShader(const std::string & path, const GLenum shaderType) {
        std::ifstream in(path);
        std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        GLuint shader = glCreateShader(shaderType); CHECK_GL_ERRORS;
        const char* src_c = src.c_str();
        const auto src_len = static_cast<GLint>(src.size());
        glShaderSource(shader, 1, &src_c, &src_len); CHECK_GL_ERRORS;
        glCompileShader(shader); CHECK_GL_ERRORS;

        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success); CHECK_GL_ERRORS;
        if (success == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength); CHECK_GL_ERRORS;
            std::vector<char> errorLog(static_cast<unsigned>(maxLength));
            glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog.data()); CHECK_GL_ERRORS;
            glDeleteShader(shader); CHECK_GL_ERRORS;
            std::cerr << errorLog.data() << std::endl;
            exit(1);
        }

        return shader;
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

    void SkeletonVisualizer::Run() {
        SimpleSceneData scene;
        scene.LoadFromFile(config.GetInputDataPath());
        GLuint PointsBuffer = scene.GenPointsBuffer();
        auto indexBufferInfo = scene.GenSkeletonIndicesBuffer();
        GLuint IndicesBuffer = std::get<0>(indexBufferInfo);
        IndicesSize = std::get<1>(indexBufferInfo);

        GLuint Program = CompileShaderProgram(
                ReadAndCompileShader("../shaders/Skeleton.vert", GL_VERTEX_SHADER),
                ReadAndCompileShader("../shaders/Skeleton.frag", GL_FRAGMENT_SHADER)
        );

        glUseProgram(Program); CHECK_GL_ERRORS;

        GLuint VAO;
        glGenVertexArrays(1, &VAO); CHECK_GL_ERRORS;
        glBindVertexArray(VAO); CHECK_GL_ERRORS;

        glBindBuffer(GL_ARRAY_BUFFER, PointsBuffer); CHECK_GL_ERRORS;
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr); CHECK_GL_ERRORS;
        glEnableVertexAttribArray(0); CHECK_GL_ERRORS;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBuffer); CHECK_GL_ERRORS;
    }

    void SkeletonVisualizer::RenderFunction() {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_LINES, static_cast<GLsizei>(IndicesSize), GL_UNSIGNED_INT, nullptr); CHECK_GL_ERRORS;
        glFinish(); CHECK_GL_ERRORS;
        glutSwapBuffers();
    }

}
