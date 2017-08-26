//
// Created by alex on 21.08.17.
//

#ifndef HORS_HORSCONFIG_H
#define HORS_HORSCONFIG_H

#include <fstream>
#include <string>

namespace Hors {

    class Program;

    class GLVersion {
    private:
        int Major;
        int Minor;

    public:
        GLVersion(const int major=3, const int minor=0): Major(major), Minor(minor) {}

        int GetMajor() const {
            return Major;
        }
        int GetMinor() const {
            return Minor;
        }

        friend std::istream& operator>>(std::istream& in, GLVersion& version) {
            char dot;
            return in >> version.Major >> dot >> version.Minor;
        }

        friend std::ostream& operator<<(std::ostream& out, const GLVersion& version) {
            return out << version.Major << '.' << version.Minor;
        }
    };



    class Config {
    private:
        GLVersion contextVersion;
        int WindowWidth;
        int WindowHeight;
        std::string WindowTitle;

    public:
        GLVersion GetGLVersion() const {
            return contextVersion;
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
        friend Program;
    };

}

#endif //HORS_HORSCONFIG_H
