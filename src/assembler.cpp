#include <iostream>

#include "headers/assembler.h"

using namespace std;

int assemble (string line){
    string args = line;

    string instr = line.substr(0, line.find(' '));

    args = args.substr(args.find(' '), line.length() - args.find(' '));


    cout << "Instruction is " << instr << endl;
    cout << "Args are" << args << endl;

    return 0;
}