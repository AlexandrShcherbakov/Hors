//
// Created by alex on 27.08.17.
//

#include <iostream>
#include <random>
#include <set>
#include <tuple>

#include "GL/glew.h"

#include "../include/SimpleSceneData.h"
#include "../include/Utils.h"

namespace Hors {

    template<GLenum Target, typename T>
    GLuint GenAndFillBuffer(const std::vector<T>& data) {
        GLuint buffer;
        glGenBuffers(1, &buffer); CHECK_GL_ERRORS;
        glBindBuffer(Target, buffer); CHECK_GL_ERRORS;
        glBufferData(Target, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS;
        glBindBuffer(Target, 0); CHECK_GL_ERRORS;
        return buffer;
    }

    void SimpleSceneData::LoadFromFile(const std::string &path) {
        std::ifstream in(path, std::ios::binary | std::ios::in);
        if (in.bad()) {
            throw std::runtime_error("File " + path + " not found.");
        }
        unsigned pointsCount;
        ReadFromBinary(in, pointsCount);
        Points.resize(pointsCount);
        for (auto &point: Points) {
            ReadFromBinary(in, point);
        }
        Normals.resize(pointsCount);
        for (auto &normal: Normals) {
            ReadFromBinary(in, normal);
        }

        unsigned trianglesIndicesCount;
        ReadFromBinary(in, trianglesIndicesCount);
        TrianglesIndices.resize(trianglesIndicesCount);
        for (auto &index: TrianglesIndices) {
            ReadFromBinary(in, index);
        }
        in.close();
    }

    void SimpleSceneData::SaveToFile(const std::string &path) const {
        std::ofstream out(path, std::ios::binary | std::ios::out);
        WriteToBinary(out, static_cast<unsigned>(Points.size()));
        for (auto &point: Points) {
            WriteToBinary(out, point);
        }
        for (auto &normal: Normals) {
            WriteToBinary(out, normal);
        }

        WriteToBinary(out, static_cast<unsigned>(TrianglesIndices.size()));
        for (auto &index: TrianglesIndices) {
            WriteToBinary(out, index);
        }
        out.close();
    }

    GLuint SimpleSceneData::GenPointsBuffer() const {
        return GenAndFillBuffer<GL_ARRAY_BUFFER>(Points);
    }

    GLuint SimpleSceneData::GenTrianglesPointsBuffer() const {
        std::vector<glm::vec4> trianglesPoints(TrianglesIndices.size());
        for (size_t i = 0; i < TrianglesIndices.size(); ++i) {
            trianglesPoints[i] = Points[TrianglesIndices[i]];
        }
        return GenAndFillBuffer<GL_ARRAY_BUFFER>(trianglesPoints);
    }

    template<typename T>
    std::pair<T, T> MakeSortedPair(const T t1, const T t2) {
        return std::make_pair(std::min(t1, t2), std::max(t1, t2));
    }

    std::tuple<GLuint, size_t> SimpleSceneData::GenSkeletonIndicesBuffer() const {
        std::set<std::pair<int, int> > edges;
        for (size_t i = 0; i < TrianglesIndices.size(); i += 3) {
            edges.insert(MakeSortedPair(TrianglesIndices[i], TrianglesIndices[i + 1]));
            edges.insert(MakeSortedPair(TrianglesIndices[i], TrianglesIndices[i + 2]));
            edges.insert(MakeSortedPair(TrianglesIndices[i + 1], TrianglesIndices[i + 2]));
        }

        std::vector<int> indices;
        for (auto &edge: edges) {
            indices.push_back(edge.first);
            indices.push_back(edge.second);
        }
        return std::make_tuple(GenAndFillBuffer<GL_ELEMENT_ARRAY_BUFFER>(indices), indices.size());
    }

    GLuint SimpleSceneData::GenRandomTrianglesColorBuffer() const {
        std::vector<glm::vec4> colors(TrianglesIndices.size());
        std::default_random_engine engine;
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        for (size_t i = 0; i < colors.size(); i += 3) {
            colors[i] = colors[i + 1] = colors[i + 2] = glm::vec4(dist(engine), dist(engine), dist(engine), 1);
        }
        return GenAndFillBuffer<GL_ARRAY_BUFFER>(colors);
    }

    GLuint SimpleSceneData::GenIndicesBuffer() const {
        return GenAndFillBuffer<GL_ELEMENT_ARRAY_BUFFER>(TrianglesIndices);
    }

    GLuint SimpleSceneData::GenIdentIndicesBuffer() const {
        std::vector<int> indices(TrianglesIndices.size());
        for (size_t i = 0; i < indices.size(); ++i) {
            indices[i] = static_cast<int>(i);
        }
        return GenAndFillBuffer<GL_ELEMENT_ARRAY_BUFFER>(indices);
    }
}
