//
// Created by alex on 26.08.17.
//

#ifndef HORS_HORSARGUMENTPARSER_H
#define HORS_HORSARGUMENTPARSER_H

#include <iostream>

#include "boost/program_options.hpp"

namespace Hors {

    namespace po = boost::program_options;

    class HorsArgumentParser {
    private:
        po::options_description Description;
        po::variables_map ParsedOptions;
    public:
        void AddArgument(const std::string& optName, const std::string& description);
        void AddArgument(
                const std::string& optName,
                const po::value_semantic* optSemantic,
                const std::string& description
        );
        void Parse(int argc, const char ** argv);
    };

}

#endif //HORS_HORSARGUMENTPARSER_H
