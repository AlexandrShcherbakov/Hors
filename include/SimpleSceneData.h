//
// Created by alex on 27.08.17.
//

#ifndef HORS_SIMPLESCENEDATA_H
#define HORS_SIMPLESCENEDATA_H

#include <fstream>
#include <string>
#include <vector>

#include "glm/vec4.hpp"

namespace Hors {

    template<typename T>
    inline void ReadFromBinary(std::istream& in, T& x) {
        in.read(reinterpret_cast<char *>(&x), sizeof(x));
    }

    template<typename T>
    inline void WriteToBinary(std::ofstream& out, const T& x) {
        out.write(reinterpret_cast<const char *>(&x), sizeof(x));
    }

    class SimpleSceneData {
    private:
        std::vector<glm::tvec4<float> > Points;
        std::vector<glm::tvec4<float> > Normals;
        std::vector<int> TrianglesIndices;
    public:
        void LoadFromFile(const std::string& path);
        void SaveToFile(const std::string &path) const;

        auto GetPoint(const unsigned index) const {
            return Points[index];
        }

        auto GetNormal(const unsigned index) const {
            return Normals[index];
        }

        auto GetTrianglesIndex(const unsigned index) const {
            return TrianglesIndices[index];
        }

        template<class InputIterator>
        void SetPoints(const InputIterator& begin, const InputIterator& end) {
            Points = {begin, end};
        }

        template<class InputIterator>
        void SetNormals(const InputIterator& begin, const InputIterator& end) {
            Normals = {begin, end};
        }

        template<class InputIterator>
        void SetTrianlesIndices(const InputIterator& begin, const InputIterator& end) {
            TrianglesIndices = {begin, end};
        }
    };

}

#endif //HORS_SIMPLESCENEDATA_H
