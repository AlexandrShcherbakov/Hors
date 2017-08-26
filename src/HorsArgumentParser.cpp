//
// Created by alex on 26.08.17.
//

#include "../include/HorsArgumentParser.h"

namespace Hors {
    void HorsArgumentParser::Parse(int argc, const char ** argv) {
        po::store(po::parse_command_line(argc, argv, Description), ParsedOptions);
        po::notify(ParsedOptions);
    }

    void HorsArgumentParser::AddArgument(
            const std::string& optName,
            const std::string& description
    ) {
        Description.add_options()
                (optName.c_str(), description.c_str());
    }

    void HorsArgumentParser::AddArgument(
            const std::string& optName,
            const po::value_semantic* optSemantic,
            const std::string& description
    ) {
        Description.add_options()
                (optName.c_str(), optSemantic, description.c_str());
    }
}