#include <iostream>

#include "headers/assembler.h"

int assemble (std::string line){
    std::string args = line;

    std::string instr = line.substr(0, line.find(' '));

    args = args.substr(args.find(' '), line.length() - args.find(' '));

    int pos = 0;
    while((pos = args.find(',')) != std::string::npos)

    std::cout << "Instruction is " << instr << std::endl;
    std::cout << "Args are" << args << std::endl;

    return 0;
}