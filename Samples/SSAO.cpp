//
// Created by alex on 10.10.17.
//

#include <random>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "HorsProgram.h"
#include "BaseMesh.h"
#include "ShaderSources.h"
#include "Utils.h"

class SSAO : public Hors::Program {
    GLuint GBufferFramebuffer = 0;
    GLuint DepthTexture = 0;
    GLuint PosTexture = 0;
    GLuint NormalTexture = 0;
    Hors::BaseMesh SceneMesh;
    GLuint GBufferRenderProgram = 0;
    GLuint MainRenderProgram = 0;

    void GenDepthRenderTarget() {
        glGenFramebuffers(1, &GBufferFramebuffer); CHECK_GL_ERRORS;
        glBindFramebuffer(GL_FRAMEBUFFER, GBufferFramebuffer); CHECK_GL_ERRORS;

        glGenTextures(1, &DepthTexture); CHECK_GL_ERRORS;
        glBindTexture(GL_TEXTURE_2D, DepthTexture); CHECK_GL_ERRORS;

        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
            Get<Hors::WindowSize>("WindowSize").GetWidth(),
            Get<Hors::WindowSize>("WindowSize").GetHeight(),
            0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr); CHECK_GL_ERRORS;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECK_GL_ERRORS;

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTexture, 0); CHECK_GL_ERRORS;

        glGenTextures(1, &PosTexture); CHECK_GL_ERRORS;
        glBindTexture(GL_TEXTURE_2D, PosTexture); CHECK_GL_ERRORS;

        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA32F,
            Get<Hors::WindowSize>("WindowSize").GetWidth(),
            Get<Hors::WindowSize>("WindowSize").GetHeight(),
            0, GL_RGBA, GL_FLOAT, nullptr); CHECK_GL_ERRORS;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECK_GL_ERRORS;

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, PosTexture, 0); CHECK_GL_ERRORS;

        glGenTextures(1, &NormalTexture); CHECK_GL_ERRORS;
        glBindTexture(GL_TEXTURE_2D, NormalTexture); CHECK_GL_ERRORS;

        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA32F,
            Get<Hors::WindowSize>("WindowSize").GetWidth(),
            Get<Hors::WindowSize>("WindowSize").GetHeight(),
            0, GL_RGBA, GL_FLOAT, nullptr); CHECK_GL_ERRORS;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECK_GL_ERRORS;

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 1, GL_TEXTURE_2D, NormalTexture, 0); CHECK_GL_ERRORS;

        GLenum status;
        status = glCheckFramebufferStatus(GL_FRAMEBUFFER); CHECK_GL_ERRORS;
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            std::cout.unsetf(std::ios::dec);
            std::cout.setf(std::ios::hex);
            std::cout << "Framebuffer error: 0x" << status << std::endl;
            std::cout.unsetf(std::ios::hex);
            std::cout.setf(std::ios::dec);
            exit(1);
        }

        GLenum buffersToDraw[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};

        glDrawBuffers(2, buffersToDraw); CHECK_GL_ERRORS;

        glBindFramebuffer(GL_FRAMEBUFFER, 0); CHECK_GL_ERRORS;
    }

    void GenDepthRenderProgram() {
        GBufferRenderProgram = Hors::CompileShaderProgram(
            Hors::CompileShader(Hors::VertexShader::SimpleGBuffer, GL_VERTEX_SHADER),
            Hors::CompileShader(Hors::FragmentShader::SimpleGBuffer, GL_FRAGMENT_SHADER)
        );

        glUseProgram(GBufferRenderProgram); CHECK_GL_ERRORS;
    }

    void GenMainRenderProgram() {
        MainRenderProgram = Hors::CompileShaderProgram(
            Hors::CompileShader(Hors::VertexShader::SimpleGBuffer, GL_VERTEX_SHADER),
            Hors::CompileShader(Hors::FragmentShader::SSAO, GL_FRAGMENT_SHADER)
        );

        glUseProgram(MainRenderProgram); CHECK_GL_ERRORS;
    }


    void GenRandomPlanesTexture() {
        const int SIDE = 4;
        const int CHANNELS = 3;
        std::vector<unsigned char> planes(SIDE * SIDE * CHANNELS);
        std::default_random_engine engine;
        std::uniform_int_distribution<unsigned char> dist(0, 255);
        for (auto& coordinate : planes) {
            coordinate = dist(engine);
        }

        GLuint randomPlanesTexture;
        glGenTextures(1, &randomPlanesTexture); CHECK_GL_ERRORS

        glActiveTexture(GL_TEXTURE0 + 3); CHECK_GL_ERRORS;
        glBindTexture(GL_TEXTURE_2D, randomPlanesTexture); CHECK_GL_ERRORS;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SIDE, SIDE, 0, GL_RGB, GL_UNSIGNED_BYTE, planes.data()); CHECK_GL_ERRORS;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CHECK_GL_ERRORS;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); CHECK_GL_ERRORS;
        Hors::SetUniform(MainRenderProgram, "RandomPlanes", 3);
    }

protected:
    void Run() override {
        MainCamera = Hors::Camera(
            glm::vec3(0, 0.025, 0), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0),
            45, Get<Hors::WindowSize>("WindowSize").GetScreenRadio(), 0.0001, 10000
        );
        GenDepthRenderTarget();
        HydraGeomData scene;
        scene.read(Get("InputFile"));
        GenDepthRenderProgram();
        SceneMesh.Init(scene);

        GenMainRenderProgram();
        SceneMesh.Bind();

        GenRandomPlanesTexture();
        glActiveTexture(GL_TEXTURE0); CHECK_GL_ERRORS;
        glBindTexture(GL_TEXTURE_2D, DepthTexture); CHECK_GL_ERRORS;
        Hors::SetUniform(MainRenderProgram, "DepthTexture", 0);
        glActiveTexture(GL_TEXTURE0 + 1); CHECK_GL_ERRORS;
        glBindTexture(GL_TEXTURE_2D, PosTexture); CHECK_GL_ERRORS;
        Hors::SetUniform(MainRenderProgram, "PosTexture", 1);
        glActiveTexture(GL_TEXTURE0 + 2); CHECK_GL_ERRORS;
        glBindTexture(GL_TEXTURE_2D, NormalTexture); CHECK_GL_ERRORS;
        Hors::SetUniform(MainRenderProgram, "NormalTexture", 2);
        Hors::SetUniform(MainRenderProgram, "ScreenWidth", Get<Hors::WindowSize>("WindowSize").GetWidth());
        Hors::SetUniform(MainRenderProgram, "ScreenHeight", Get<Hors::WindowSize>("WindowSize").GetHeight());

        glEnable(GL_DEPTH_TEST); CHECK_GL_ERRORS;
    }

    void RenderFunction() override {
        glBindFramebuffer(GL_FRAMEBUFFER, GBufferFramebuffer); CHECK_GL_ERRORS;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERRORS;

        glUseProgram(GBufferRenderProgram); CHECK_GL_ERRORS;
        Hors::SetUniform(GBufferRenderProgram, "CameraMatrix", MainCamera.GetMatrix());
        glDrawElements(GL_TRIANGLES, SceneMesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr); CHECK_GL_ERRORS;
        glFinish(); CHECK_GL_ERRORS;

        glBindFramebuffer(GL_FRAMEBUFFER, 0); CHECK_GL_ERRORS;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERRORS;
        glUseProgram(MainRenderProgram); CHECK_GL_ERRORS;
        Hors::SetUniform(MainRenderProgram, "CameraMatrix", MainCamera.GetMatrix());
        glDrawElements(GL_TRIANGLES, SceneMesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr); CHECK_GL_ERRORS;
        glFinish(); CHECK_GL_ERRORS;
        glutSwapBuffers();
    }
};

int main(int argc, char** argv) {
    Hors::RunProgram<SSAO>(argc, argv);
}