//
// Created by alex on 21.08.17.
//

#ifndef HORS_HORS_CONFIG_H
#define HORS_HORS_CONFIG_H

#include <fstream>
#include <string>

#include "HorsArgumentParser.h"

namespace Hors {

    class Config {
    private:
        HorsArgumentParser Parser;
        std::map<std::string, std::string> AllArgs;
        std::string configFile;

        void LoadFromFile(const std::string& path);
    public:
        Config();

        template<typename T>
        void AddArgument(const std::string& argName, const T& defaultValue, const std::string& description) {
            std::stringstream ss;
            ss << defaultValue;
            AllArgs[argName] = ss.str();
            Parser.AddArgument(argName, po::value<std::string>(&(AllArgs[argName])), description);
        }

        std::string Get(const std::string& argName) {
            return AllArgs[argName];
        }

        template<typename T>
        T Get(const std::string& argName) {
            static std::map<std::string, T> cache;
            auto cachedIt = cache.find(argName);
            if (cachedIt != cache.end()) {
                return cachedIt->second;
            }
            auto globalIt = AllArgs.find(argName);
            assert(globalIt != AllArgs.end());
            std::stringstream ss(globalIt->second);
            ss >> cache[argName];
            return cache[argName];
        }

        void Init(int argc, const char ** argv);
    };

}

#endif //HORS_HORS_CONFIG_H
