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
        GLVersion() = default;
        GLVersion(const int major, const int minor): Major(major), Minor(minor) {}

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

    class WindowSize {
    private:
        int Width;
        int Height;
    public:
        WindowSize() = default;
        WindowSize(const int width, const int height): Width(width), Height(height) {}

        int GetWidth() const {
            return Width;
        }
        int GetHeight() const {
            return Height;
        }

        friend std::istream& operator>>(std::istream& in, WindowSize& size) {
            char x;
            return in >> size.Width >> x >> size.Height;
        }

        friend std::ostream& operator<<(std::ostream& out, const WindowSize& size) {
            return out << size.Width << 'x' << size.Height;
        }
    };

    class Config {
        friend Program;
    private:
        GLVersion contextVersion;
        WindowSize windowSize;
        std::string WindowTitle;

    public:
        void LoadFromFile(const std::string& path);

        friend std::istream& operator>>(std::istream& in, Config& config) {
            std::string path;
            in >> path;
            config.LoadFromFile(path);
            return in;
        }

        friend std::ostream& operator<<(std::ostream& out, const Config& config) {
            return out << "Window Title: " << config.WindowTitle << std::endl
                << "Window size: " << config.windowSize << std::endl
                << "OpenGL context version: " << config.contextVersion << std::endl;
        }

        const GLVersion GetGLVersion() const {
            return contextVersion;
        }

        const WindowSize GetWindowSize() const {
            return windowSize;
        }

        const std::string GetWindowTitle() const {
            return WindowTitle;
        }
    };

}

#endif //HORS_HORSCONFIG_H
