//
// Created by alex on 26.08.17.
//

#ifndef HORS_HORS_ARGUMENT_PARSER_H
#define HORS_HORS_ARGUMENT_PARSER_H

#include <iostream>

#include "boost/program_options.hpp"

namespace Hors {

    namespace po = boost::program_options;

    class HorsArgumentParser {
    private:
        po::options_description Description = po::options_description();
        po::variables_map ParsedOptions = po::variables_map();
    public:
        void AddArgument(
                const std::string& optName,
                const po::value_semantic* optSemantic,
                const std::string& description
        );
        void Parse(int argc, const char ** argv);
    };

}

#endif //HORS_HORS_ARGUMENT_PARSER_H
