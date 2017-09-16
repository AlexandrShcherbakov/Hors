//
// Created by alex on 27.08.17.
//

#ifndef HORS_SIMPLE_SCENE_DATA_H
#define HORS_SIMPLE_SCENE_DATA_H

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

        template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
        void SetPoints(const _InputIterator& begin, const _InputIterator& end) {
            Points = {begin, end};
        }

        template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
        void SetNormals(const _InputIterator& begin, const _InputIterator& end) {
            Normals = {begin, end};
        }

        template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
        void SetTrianglesIndices(const _InputIterator &begin, const _InputIterator &end) {
            TrianglesIndices = {begin, end};
        }

        GLuint GenPointsBuffer() const;
        std::tuple<GLuint, size_t> GenSkeletonIndicesBuffer() const;
    };

}

#endif //HORS_SIMPLE_SCENE_DATA_H
