//
// Created by alex on 21.08.17.
//

#include "boost/property_tree/json_parser.hpp"

#include "HorsConfig.h"

namespace Hors {

    namespace pt = boost::property_tree;

    GLVersion ExtractGLVersionFromPTree(const pt::ptree& tree) {
        return {tree.get<int>("Major"), tree.get<int>("Minor")};
    }

    WindowSize ExtractWindowSizeFromPTree(const pt::ptree& tree) {
        return {tree.get<int>("Width"), tree.get<int>("Height")};
    }

    void Config::LoadFromFile(const std::string &path) {
        pt::ptree tree;
        pt::read_json(path, tree);
        WindowTitle = tree.get<std::string>("Window Title", "Hors Program");
        InputDataPath = tree.get<std::string>("Input Data Path", "");
        if (tree.count("GLVersion")) {
            contextVersion = ExtractGLVersionFromPTree(tree.get_child("GLVersion"));
        }
        if (tree.count("Window Size")) {
            windowSize = ExtractWindowSizeFromPTree(tree.get_child("Window Size"));
        }
    }
}