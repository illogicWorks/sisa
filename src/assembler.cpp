#include "headers/assembler.h"
#include "headers/utils.h"

#include <iostream>
#include <map>

std::vector<std::string> mathops = {"AND", "OR", "XOR", "NOT", "ADD", "SUB", "SHA", "SHL"};
std::vector<std::string> cmpops = {"CMPLT", "CMPLE", "-", "CMPEQ", "CMPLTU", "CMPLEU", "-", "-"};

std::map<std::string, int> tworegops = {
    { "ADDI", 0 },
    { "LD", 1 },
    { "ST", 2 },
    { "LDB", 1 },
    { "STB", 2 },
    { "JALR", 3 }
};

void splitString(std::string str, std::vector<std::string>& argVec, std::string delimiter){
    int pos = 0;
    std::string token;
    // Separate args
    while((pos = str.find(delimiter)) != std::string::npos){
        token = str.substr(0, pos);
        
        argVec.push_back(token);

        str.erase(0, pos + delimiter.length());
    }

     argVec.push_back(str);
}

unsigned short int assemble (std::string line, bool& error){
    // Keep string copy
    std::string args = line;

    // Separate instruction from arguments
    args = args.substr(args.find(' ') + 1, line.length() - args.find(' ') + 1); // +1 to remove the delemiter which has length

    std::string instr = line.substr(0, line.find(' '));

    debug("Instruction", instr, 2);

    std::bitset<4> op;
    std::bitset<3> f;
    int order = 0;

    int regType = getOpcode(instr, op, f, order);
    debug("Regtype", regType, 2);
    debug("Opcode", op, 2);
    debug("Func", f, 2);
    debug("InstrOrder", order, 2);

    // Separate args
    std::vector<std::string> argVec;
    splitString(args, argVec, ", ");
    
    // Encode based on register type
    if(regType == 3){

        if(instr == "NOT" && argVec.size() < 2){
            debug("ERROR", "Missing register at operand " + instr + " at line TODO", 1);
            error = true;
            return 0;
        }
        if(instr != "NOT" && argVec.size() < 3){
            debug("ERROR", "Missing register at operand " + instr + " at line TODO", 1);
            error = true;
            return 0;
        }

        std::bitset<3> regD (argVec[0][1]);
        std::bitset<3> regA (argVec[1][1]);
        std::bitset<3> regB;

        if(instr == "NOT"){
            regB = std::bitset<3> (0);
        }else{
            regB = std::bitset<3> (argVec[2][1]);
        }

        debug("D", regD, 2);
        debug("A", regA, 2);
        debug("B", regB, 2);

        std::bitset<16> encInstr(op.to_string() + regA.to_string() + regB.to_string() + regD.to_string() + f.to_string());
        unsigned short int result = encInstr.to_ulong();

        debug("Encoded", encInstr, 1, false);
        debugHex(result, 1);
        
        return result;
    }else if (regType == 2){
        std::bitset<6> N;
        std::bitset<3> regA;
        std::bitset<3> regBD; // B OR D

        std::vector<std::string> splitArgs;

        switch (order)
        {
            case 0:
                regBD = std::bitset<3>(argVec[0][1]);
                regA = std::bitset<3>(argVec[1][1]);
                N = std::bitset<6>(std::stoi(argVec[2]));
                break;
            case 1:
                regBD = std::bitset<3>(argVec[0][1]);
                splitString(argVec[1], splitArgs, "(");

                N = std::bitset<6>(std::stoi(splitArgs[0]));
                regA = std::bitset<3>(splitArgs[1][1]);
                break;
            case 2:
                regBD = std::bitset<3>(argVec[1][1]);
                splitString(argVec[0], splitArgs, "(");

                N = std::bitset<6>(std::stoi(splitArgs[0]));
                regA = std::bitset<3>(splitArgs[1][1]);

                break;
             case 3:
                regBD = std::bitset<3>(argVec[0][1]);
                regA = std::bitset<3>(argVec[1][1]);
                N = std::bitset<6>(0);

                break;
        }

        debug("BD", regBD, 2);
        debug("N", N, 2);
        debug("A", regA, 2);

        std::bitset<16> encInstr(op.to_string() + regA.to_string() + regBD.to_string() + N.to_string());
        unsigned short int result = encInstr.to_ulong();

        debug("Encoded", encInstr, 1, false);
        debugHex(result, 1);
        
        return result;

    }else if (regType == 1){

    }else{
        debug("ERROR", "Unkown instruction " + instr + " at line TODO", 1);
    }

    return 0;
}


int getOpcode (std::string instr, std::bitset<4>& op, std::bitset<3>& f, int& order){
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
            op = 0b0001;
            f = i;
            return 3;
        }
    }


    // Two register format INS REGA, REGB/D, N
    int i = 2;
    for (auto const& [key, val] : tworegops)
    {
        if(instr == key) {
            op = i;
            order = val;
            return 2;
        }
        i++;
    }
    

    // One register format INS REGA, N
    return -1;
}
