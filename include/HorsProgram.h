#ifndef HORS_LIBRARY_H
#define HORS_LIBRARY_H

class HorsProgram {
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