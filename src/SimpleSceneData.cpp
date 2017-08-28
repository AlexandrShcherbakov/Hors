//
// Created by alex on 27.08.17.
//

#include "../include/SimpleSceneData.h"

namespace Hors {

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
}
