//
// Created by alex on 27.08.17.
//

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/gtc/type_ptr.hpp"

#include "../include/SimpleSceneData.h"
#include "../include/SkeletonVisualizer.h"
#include "../include/Utils.h"

namespace Hors {

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

        CameraUniformLocation = glGetUniformLocation(Program, "CameraMatrix"); CHECK_GL_ERRORS;

        MainCamera = Camera(
            glm::vec3(0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0),
            45, config.GetWindowSize().GetScreenRadio(), 0.0001, 10000
        );
    }

    void SkeletonVisualizer::RenderFunction() {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(CameraUniformLocation, 1, GL_FALSE, glm::value_ptr(MainCamera.GetMatrix())); CHECK_GL_ERRORS;
        glDrawElements(GL_LINES, static_cast<GLsizei>(IndicesSize), GL_UNSIGNED_INT, nullptr); CHECK_GL_ERRORS;
        glFinish(); CHECK_GL_ERRORS;
        glutSwapBuffers();
    }

}
