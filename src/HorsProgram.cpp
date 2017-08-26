//
// Created by alex on 21.08.17.
//

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../include/HorsProgram.h"

namespace Hors {

    class GlobalFunctionContainer {
    private:
        GlobalFunctionContainer() = default;
        std::function<void(const unsigned char)> KeyboardFunction;
        std::function<void(const int)> SpecialButtonsFunction;

    public:
        static GlobalFunctionContainer& Get() {
            static GlobalFunctionContainer singleton;
            return singleton;
        }

        void SetKeyboardFunction(const std::function<void(const unsigned char)>& func) {
            KeyboardFunction = func;
        }

        void CallKeyboardFunction(const unsigned char key) const {
            KeyboardFunction(key);
        }

        void SetSpecialButtonsFunction(const std::function<void(const int)>& func) {
            SpecialButtonsFunction = func;
        }

        void CallSpecialButtonsFunction(const int key) const {
            SpecialButtonsFunction(key);
        }
    };

    void KeyboardFunction(unsigned char key, int x, int y) {
        GlobalFunctionContainer::Get().CallKeyboardFunction(key);
    }

    void SpecialButtonFunction(int key, int x, int y) {
        GlobalFunctionContainer::Get().CallSpecialButtonsFunction(key);
    }

    void InitGlut(const Config &config, int argc, char **argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
        glutInitContextVersion(config.GetGLContextMajorVersion(), config.GetGLContextMinorVersion());
        glutInitWindowSize(config.GetWindowWidth(), config.GetWindowHeight());
        glutCreateWindow(config.GetWindowTitle().c_str());
        glutKeyboardFunc(KeyboardFunction);
        glutSpecialFunc(SpecialButtonFunction);
    }

    void Program::SetGlobalFunctions() {
        GlobalFunctionContainer::Get().SetKeyboardFunction(
                [this](const unsigned char key) { this->KeyboardFunction(key); }
        );
        GlobalFunctionContainer::Get().SetSpecialButtonsFunction(
                [this](const int key) { this->SpecialButtons(key); }
        );
    }

    void RunInitialFunctions(std::vector<std::function<void(void)> >& funcs) {
        for (auto& func: funcs) {
            func();
        }
    }

    void Program::RunFullProcess(int argc, char **argv) {
        Parser.Parse(argc, const_cast<const char **>(argv));
        SetGlobalFunctions();
        InitGlut(config, argc, argv);
        glewInit();
        RunInitialFunctions(InitialFunctions);
        glutMainLoop();
    }

}