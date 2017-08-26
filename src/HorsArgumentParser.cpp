//
// Created by alex on 26.08.17.
//

#include "../include/HorsArgumentParser.h"

namespace Hors {
    void HorsArgumentParser::Parse(int argc, const char ** argv) {
        po::store(po::parse_command_line(argc, argv, Description), ParsedOptions);
        po::notify(ParsedOptions);
    }
}