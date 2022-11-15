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

    int regType = getOpcode(instr, op, f);
    std::cout << "Regtype: " << regType << std::endl;
    std::cout << "Opcode: " << op << std::endl;
    std::cout << "Func: " << f << std::endl;

    int pos = 0;
    std::string delimiter = ", ";
    std::string token;
    std::vector<std::string> argVec;
    
    // Separate args
    while((pos = args.find(delimiter)) != std::string::npos){
        token = args.substr(0, pos);
        
        argVec.push_back(token);

        args.erase(0, pos + delimiter.length());
    }

     argVec.push_back(args);

    if(regType == 3){
        std::bitset<3> regD (argVec[0][1]);
        std::bitset<3> regA (argVec[1][1]);
        std::bitset<3> regB (argVec[2][1]);



        std::cout << "D: " << regD << std::endl;
        std::cout << "A: " << regA << std::endl;
        std::cout << "B: " << regB << std::endl;
    }

    return 0;
}


int getOpcode (std::string instr, std::bitset<4>& op, std::bitset<3>& f){
    // Three register format INS REGD, REGA, REGB
    for(int i = 0; i < mathops.size(); i++){
        if(instr == mathops[i]) {
            op = 0b0000;
            f = i;
            return 3;
        }
    }

    for(int i = 0; i < cmpops.size(); i++){
        if(instr == cmpops[i]) {
            op = 0b0001;;
            f = i;
            return 3;
        }
    }

    // Two register format INS REGA, REGB/D, N

    // One register format INS REGA, N
    return -1;
}