//
// Created by alex on 21.08.17.
//

#ifndef HORS_LIBRARY_H
#define HORS_LIBRARY_H

#include "HorsConfig.h"

class HorsProgram {
private:
    HorsConfig config;

protected:
    void RunFullProcess(int argc, char ** argv);

public:
    ///Constructors
    HorsProgram();

    template <typename ProgramClass>
    friend void RunProgram(int argc, char ** argv);
};

template <typename ProgramClass>
inline void RunProgram(int argc, char ** argv) {
    ProgramClass p;
    p.RunFullProcess(argc, argv);
}

#endif