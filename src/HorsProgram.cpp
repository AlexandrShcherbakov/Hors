//
// Created by alex on 21.08.17.
//

#include "../include/HorsProgram.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

HorsProgram::HorsProgram() {

}

void InitGlut(const HorsConfig& config, int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitContextVersion(config.GetGLContextMajorVersion(), config.GetGLContextMinorVersion());
    glutInitWindowSize(config.GetWindowWidth(), config.GetWindowHeight());
    glutCreateWindow(config.GetWindowTitle().c_str());
}

void HorsProgram::RunFullProcess(int argc, char **argv) {
    InitGlut(config, argc, argv);
    glewInit();
    glutMainLoop();
}
