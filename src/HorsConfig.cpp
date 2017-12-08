//
// Created by alex on 21.08.17.
//

#include "boost/property_tree/json_parser.hpp"

#include "HorsConfig.h"

namespace Hors {
    namespace pt = boost::property_tree;

    Config::Config() {
        Parser.AddArgument("config", po::value(&configFile), "Path to configuration file");
    }

    void Config::Init(int argc, const char ** argv) {
        Parser.Parse(argc, argv);
        if (!configFile.empty()) {
            LoadFromFile(configFile);
            Parser.Parse(argc, argv);
        }
    }

    void Config::LoadFromFile(const std::string &path) {
        pt::ptree tree;
        pt::read_json(path, tree);
        for (auto& it: tree) {
            AllArgs[it.first] = it.second.data();
        }
    }
}