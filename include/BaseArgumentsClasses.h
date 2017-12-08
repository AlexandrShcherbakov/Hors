//
// Created by alex on 08.12.17.
//

#ifndef HORS_BASEARGUMENTSCLASSES_H
#define HORS_BASEARGUMENTSCLASSES_H

#include <iostream>

#include "BaseArgumentsClasses.h"

namespace Hors {

    class GLVersion {
    private:
        int Major = 3;
        int Minor = 0;

    public:
        GLVersion() = default;

        GLVersion(const int major, const int minor) : Major(major), Minor(minor) {}

        int GetMajor() const {
            return Major;
        }

        int GetMinor() const {
            return Minor;
        }

        friend std::istream &operator>>(std::istream &in, GLVersion &version) {
            char dot;
            return in >> version.Major >> dot >> version.Minor;
        }

        friend std::ostream &operator<<(std::ostream &out, const GLVersion &version) {
            return out << version.Major << '.' << version.Minor;
        }
    };

    class WindowSize {
    private:
        int Width = 1024;
        int Height = 768;
    public:
        WindowSize() = default;

        WindowSize(const int width, const int height) : Width(width), Height(height) {}

        int GetWidth() const {
            return Width;
        }

        int GetHeight() const {
            return Height;
        }

        float GetScreenRadio() const {
            return static_cast<float>(Width) / static_cast<float>(Height);
        }

        friend std::istream &operator>>(std::istream &in, WindowSize &size) {
            char x;
            return in >> size.Width >> x >> size.Height;
        }

        friend std::ostream &operator<<(std::ostream &out, const WindowSize &size) {
            return out << size.Width << 'x' << size.Height;
        }
    };

}
#endif //HORS_BASEARGUMENTSCLASSES_H
