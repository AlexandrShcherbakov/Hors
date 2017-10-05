//
// Created by alex on 21.08.17.
//

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "../include/HorsProgram.h"

namespace Hors {

    class GlobalFunctionContainer {
    private:
        GlobalFunctionContainer() = default;
        const std::function<void(const unsigned char)> DefaultKeyboardFunction = [](const unsigned char){};
        const std::function<void(const int)> DefaultSpecialButtonsFunction = [](const int){};
        const std::function<void(void)> DefaultRenderFunction = []{};
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

        void SetDefaults() {
            KeyboardFunction = DefaultKeyboardFunction;
            SpecialButtonsFunction = DefaultSpecialButtonsFunction;
            RenderFunction = DefaultRenderFunction;
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

    int InitGlut(const Config &config, int argc, char **argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
        glutInitContextVersion(config.GetGLVersion().GetMajor(), config.GetGLVersion().GetMinor());
        glutInitWindowSize(config.GetWindowSize().GetWidth(), config.GetWindowSize().GetHeight());
        int windowId = glutCreateWindow(config.GetWindowTitle().c_str());
        glutKeyboardFunc(KeyboardFunction);
        glutSpecialFunc(SpecialButtonFunction);
        glutDisplayFunc(RenderFunction);
        glutIdleFunc(glutPostRedisplay);
        return windowId;
    }

    void RunInitialFunctions(std::vector<std::function<void(void)> >& funcs) {
        for (auto& func: funcs) {
            func();
        }
    }

    void Program::AddInitializeArguments() {
        Parser.AddArgument("config", po::value(&config), "Path to configuration file");
        Parser.AddArgument("gl_version", po::value(&(config.contextVersion)), "Version of OpenGL context");
        Parser.AddArgument("title", po::value(&(config.WindowTitle)), "Window title");
        Parser.AddArgument("window_size", po::value(&(config.windowSize)), "Window size");
    }

    void Program::AddKeyboardEvents() {
        AddKeyboardEvent(static_cast<char>(27), [this]() { CloseWindow(); });
        AddKeyboardEvent('w', [this]() { MainCamera.StepForward(); });
        AddKeyboardEvent('s', [this]() { MainCamera.StepBackward(); });
        AddKeyboardEvent(GLUT_KEY_UP, [this] { MainCamera.RotateTop(); });
        AddKeyboardEvent(GLUT_KEY_DOWN, [this] { MainCamera.RotateDown(); });
        AddKeyboardEvent(GLUT_KEY_LEFT, [this] { MainCamera.RotateLeft(); });
        AddKeyboardEvent(GLUT_KEY_RIGHT, [this] { MainCamera.RotateRight(); });
    }

    Program::Program() {
        AddInitializeArguments();
        AddKeyboardEvents();
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
        WindowID = InitGlut(config, argc, argv);
        GLenum err = glewInit();
        if (GLEW_OK != err) {
            std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
            exit(1);
        }
        RunInitialFunctions(InitialFunctions);
        Run();
        glutMainLoop();
    }

    void Program::CloseWindow() const {
        GlobalFunctionContainer::Get().SetDefaults();
        glutLeaveMainLoop();
        glutDestroyWindow(WindowID);
    }
}