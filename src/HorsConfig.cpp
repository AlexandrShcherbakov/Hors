//
// Created by alex on 21.08.17.
//

#include "boost/property_tree/json_parser.hpp"

#include "../include/HorsConfig.h"

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
        contextVersion = GLVersion(3, 0);
        if (tree.count("GLVersion") != 0) {
            contextVersion = ExtractGLVersionFromPTree(tree.get_child("GLVersion"));
        }
        windowSize = WindowSize(1024, 768);
        if (tree.count("Window Size") != 0) {
            windowSize = ExtractWindowSizeFromPTree(tree.get_child("Window Size"));
        }
    }
}