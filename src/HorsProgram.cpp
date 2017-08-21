#include "../include/HorsProgram.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

HorsProgram::HorsProgram() {

}

void InitGlut(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitContextVersion(3, 0);
    glutInitWindowPosition(40, 40);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("TODO: Config name");
    glutWarpPointer(400, 300);
    glutSetCursor(GLUT_CURSOR_NONE);
}

void HorsProgram::RunFullProcess(int argc, char **argv) {
    InitGlut(argc, argv);
    glewInit();
    glutMainLoop();
}

