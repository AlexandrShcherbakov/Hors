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
        std::function<void(void)> RenderFunction;

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

        void SetRenderFunction(const std::function<void(void)>& func) {
            RenderFunction = func;
        }

        void CallRenderFunction() const {
            RenderFunction();
        }
    };

    void KeyboardFunction(unsigned char key, int x, int y) {
        GlobalFunctionContainer::Get().CallKeyboardFunction(key);
    }

    void SpecialButtonFunction(int key, int x, int y) {
        GlobalFunctionContainer::Get().CallSpecialButtonsFunction(key);
    }

    void RenderFunction() {
        GlobalFunctionContainer::Get().CallRenderFunction();
    }

    void InitGlut(const Config &config, int argc, char **argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
        glutInitContextVersion(config.GetGLVersion().GetMajor(), config.GetGLVersion().GetMinor());
        glutInitWindowSize(config.GetWindowSize().GetWidth(), config.GetWindowSize().GetHeight());
        glutCreateWindow(config.GetWindowTitle().c_str());
        glutKeyboardFunc(KeyboardFunction);
        glutSpecialFunc(SpecialButtonFunction);
        glutDisplayFunc(RenderFunction);
    }

    void RunInitialFunctions(std::vector<std::function<void(void)> >& funcs) {
        for (auto& func: funcs) {
            func();
        }
    }

    Program::Program() {
        Parser.AddArgument("config", po::value(&config), "Path to configuration file");
        Parser.AddArgument("gl_version", po::value(&(config.contextVersion)), "Version of OpenGL context");
        Parser.AddArgument("title", po::value(&(config.WindowTitle)), "Window title");
        Parser.AddArgument("window_size", po::value(&(config.windowSize)), "Window size");
    }

    void Program::SetGlobalFunctions() {
        GlobalFunctionContainer::Get().SetKeyboardFunction(
                [this](const unsigned char key) { this->KeyboardFunction(key); }
        );
        GlobalFunctionContainer::Get().SetSpecialButtonsFunction(
                [this](const int key) { this->SpecialButtons(key); }
        );
        GlobalFunctionContainer::Get().SetRenderFunction(
                [this]() { this->RenderFunction(); }
        );
    }

    void Program::RunFullProcess(int argc, char **argv) {
        Parser.Parse(argc, const_cast<const char **>(argv));
        SetGlobalFunctions();
        InitGlut(config, argc, argv);
        glewInit();
        RunInitialFunctions(InitialFunctions);
        Run();
        glutMainLoop();
    }

}