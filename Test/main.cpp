//
// Created by alex on 21.08.17.
//

#include <iostream>

#include "../include/HorsProgram.h"

class TestProgram : public Hors::Program {
public:
    TestProgram() {
        AddKeyboardEvent(static_cast<unsigned char>(27), []() {exit(0);});
        AddInitialFunction([]() {std::cout << "Initial function works" << std::endl; });
    }
    virtual void Run() {
        std::cout << "Run test program" << std::endl;
    }
    virtual void RenderFunction() {

    }
};

int main(int argc, char ** argv) {
    Hors::RunProgram<TestProgram>(argc, argv);
}