//
// Created by alex on 21.08.17.
//

#include "../include/HorsProgram.h"

class TestProgram : public Hors::Program {
public:
    TestProgram() {
        AddKeyboardEvent(static_cast<unsigned char>(27), []() {exit(0);});
    }
};

int main(int argc, char ** argv) {
    Hors::RunProgram<TestProgram>(argc, argv);
}