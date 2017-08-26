//
// Created by alex on 21.08.17.
//

#ifndef HORS_LIBRARY_H
#define HORS_LIBRARY_H

#include <functional>
#include <map>

#include "HorsArgumentParser.h"
#include "HorsConfig.h"

namespace Hors {

    class Program {
    private:
        Config config;
        HorsArgumentParser Parser;
        std::map<char, std::function<void(void)> > KeyboardEvents;
        std::map<int, std::function<void(void)> > SpecialButtonsEvents;

        void SetGlobalFunctions();
        void KeyboardFunction(const unsigned char key) {
            return KeyboardEvents[key]();
        }
        void SpecialButtons(const int key) {
            return SpecialButtonsEvents[key]();
        }

    protected:
        void RunFullProcess(int argc, char **argv);
        template<typename ProgramClass>
        friend void RunProgram(int argc, char **argv);

        void AddKeyboardEvent(const unsigned char key, std::function<void(void)> func) {
            KeyboardEvents[key] = func;
        }
        void AddKeyboardEvent(const int key, std::function<void(void)> func) {
            SpecialButtonsEvents[key] = func;
        }

    public:
        virtual ~Program()= default;
    };

    template<typename ProgramClass>
    inline void RunProgram(int argc, char **argv) {
        ProgramClass p;
        p.RunFullProcess(argc, argv);
    }

}
#endif