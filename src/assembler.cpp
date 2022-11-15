#include "headers/assembler.h"

std::vector<std::string> mathops = {"AND", "OR", "XOR", "NOT", "ADD", "SUB", "SHA", "SHL"};
std::vector<std::string> cmpops = {"CMPLT", "CMPLE", "-", "CMPEQ", "CMPLTU", "CMPLEU", "-", "-"};

int assemble (std::string line){
    // Keep string copy
    std::string args = line;

    // Separate instruction from arguments
    args = args.substr(args.find(' ') + 1, line.length() - args.find(' ') + 1); // +1 to remove the delemiter which has length

    std::string instr = line.substr(0, line.find(' '));

    std::cout << "Instruction is " << instr << std::endl;

    std::bitset<4> op;
    std::bitset<3> f;

    getOpcode(instr, op, f);
    std::cout << "Opcode: " << op << std::endl;
    std::cout << "Func: " << f << std::endl;

    // Get parameters
    int pos = 0;
    std::string delimiter = ", ";
    std::string token;

    while((pos = args.find(delimiter)) != std::string::npos){
        token = args.substr(0, pos);
        
        std::cout << token << std::endl;

        args.erase(0, pos + delimiter.length());
    }

    std::cout << args << std::endl;

    return 0;
}

void getOpcode (std::string instr, std::bitset<4>& op, std::bitset<3>& f){
    for(int i = 0; i < mathops.size(); i++){
        if(instr == mathops[i]) {
            op = 0b0000;
            f = i;
            return;
        }
    }

    for(int i = 0; i < cmpops.size(); i++){
        if(instr == cmpops[i]) {
            op = 0b0001;;
            f = i;
            return;
        }
    }
}