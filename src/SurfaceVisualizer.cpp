//
// Created by alex on 05.10.17.
//

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/gtc/type_ptr.hpp"

#include "../include/SimpleSceneData.h"
#include "../include/SurfaceVisualizer.h"
#include "../include/Utils.h"

namespace Hors {
    void SurfaceVisualizer::Run() {
        SimpleSceneData scene;
        scene.LoadFromFile(config.GetInputDataPath());
        GLuint PointsBuffer = scene.GenTrianglesPointsBuffer();
        GLuint IndicesBuffer = scene.GenIdentIndicesBuffer();
        IndicesSize = scene.GetTrianglesIndicesSize();
        GLuint ColorsBuffer = scene.GenRandomTrianglesColorBuffer();

        GLuint Program = CompileShaderProgram(
            ReadAndCompileShader("../shaders/Surface.vert", GL_VERTEX_SHADER),
            ReadAndCompileShader("../shaders/Surface.frag", GL_FRAGMENT_SHADER)
        );

        glUseProgram(Program); CHECK_GL_ERRORS;

        GLuint VAO;
        glGenVertexArrays(1, &VAO); CHECK_GL_ERRORS;
        glBindVertexArray(VAO); CHECK_GL_ERRORS;

        glBindBuffer(GL_ARRAY_BUFFER, PointsBuffer); CHECK_GL_ERRORS;
        glEnableVertexAttribArray(0); CHECK_GL_ERRORS;
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr); CHECK_GL_ERRORS;

        glBindBuffer(GL_ARRAY_BUFFER, ColorsBuffer); CHECK_GL_ERRORS;
        glEnableVertexAttribArray(1); CHECK_GL_ERRORS;
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr); CHECK_GL_ERRORS;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBuffer); CHECK_GL_ERRORS;

        CameraUniformLocation = glGetUniformLocation(Program, "CameraMatrix"); CHECK_GL_ERRORS;

        MainCamera = Camera(
            glm::vec3(0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0),
            45, config.GetWindowSize().GetScreenRadio(), 0.0001, 10000
        );
    }

    void SurfaceVisualizer::RenderFunction() {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(CameraUniformLocation, 1, GL_FALSE, glm::value_ptr(MainCamera.GetMatrix())); CHECK_GL_ERRORS;
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(IndicesSize), GL_UNSIGNED_INT, nullptr); CHECK_GL_ERRORS;
        glFinish(); CHECK_GL_ERRORS;
        glutSwapBuffers();
    }
}