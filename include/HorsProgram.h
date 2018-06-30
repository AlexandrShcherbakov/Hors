//
// Created by alex on 21.08.17.
//

#ifndef HORS_LIBRARY_H
#define HORS_LIBRARY_H

#include <functional>
#include <map>

#include <GL/glew.h>

#include "Camera.h"
#include "HorsArgumentParser.h"
#include "HorsConfig.h"
#include "BaseArgumentsClasses.h"

namespace Hors {

    class Program {
    private:
        std::map<char, std::function<void(void)> > KeyboardEvents = {};
        std::map<int, std::function<void(void)> > SpecialButtonsEvents = {};
        std::vector<std::function<void(void)> > InitialFunctions = {};
        Config config = Config();

        void InitGlut(int argc, char **argv);
        void AddInitializeArguments();
        void AddKeyboardEvents();
        void SetGlobalFunctions();
        void KeyboardFunction(const unsigned char key) {
            if (KeyboardEvents.count(key)) {
                KeyboardEvents[key]();
            }
        }
        void SpecialButtons(const int key) {
            if (SpecialButtonsEvents.count(key)) {
                SpecialButtonsEvents[key]();
            }
        }
        virtual void RenderFunction() = 0;
        virtual void Run() = 0;

    protected:
        GLint CameraUniformLocation = -1;
        Camera MainCamera = Camera();

        void RunFullProcess(int argc, char **argv);
        template<typename ProgramClass>
        friend void RunProgram(int argc, char **argv);

        void AddKeyboardEvent(const char key, std::function<void(void)>&& func) {
            KeyboardEvents[key] = func;
        }
        void AddKeyboardEvent(const int key, std::function<void(void)>&& func) {
            SpecialButtonsEvents[key] = func;
        }
        void AddInitialFunction(std::function<void(void)>&& func) {
            InitialFunctions.push_back(func);
        }
        void CloseWindow() const;

    public:
        Program();
        Program(const Program&) = default;
        Program(Program&&) = default;
        Program& operator=(const Program&) = default;
        Program& operator=(Program&&) = default;

        template<typename T>
        T Get(const std::string& paramName) {
            return config.Get<T>(paramName);
        }

        std::string Get(const std::string& paramName) {
            return config.Get(paramName);
        }

        template<typename T>
        void AddArgument(const std::string& paramName, const T& defaultValue, const std::string& description="") {
            return config.AddArgument(paramName, defaultValue, description);
        }

        virtual ~Program() = default;
    };

    template<typename ProgramClass>
    inline void RunProgram(int argc, char **argv) {
        ProgramClass p;
        p.RunFullProcess(argc, argv);
    }

}
#endif