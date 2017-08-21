//
// Created by alex on 21.08.17.
//

#ifndef HORS_HORSCONFIG_H
#define HORS_HORSCONFIG_H

#include <string>

namespace Hors {

    class Program;

    class Config {
        friend Program;

    private:
        int GLContextMajorVersion = 3;
        int GLContextMinorVersion = 0;
        int WindowWidth = 1024;
        int WindowHeight = 768;
        std::string WindowTitle = "Hors Program";

    public:
        int GetGLContextMajorVersion() const {
            return GLContextMajorVersion;
        }

        int GetGLContextMinorVersion() const {
            return GLContextMinorVersion;
        }

        int GetWindowWidth() const {
            return WindowWidth;
        }

        int GetWindowHeight() const {
            return WindowHeight;
        }

        std::string GetWindowTitle() const {
            return WindowTitle;
        }
    };

}

#endif //HORS_HORSCONFIG_H
