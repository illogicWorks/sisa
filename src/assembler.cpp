#include "headers/assembler.h"
#include "headers/utils.h"
#include "headers/strings.h"

#include <iostream>
#include <map>

std::vector<std::string> mathops = {"AND", "OR", "XOR", "NOT", "ADD", "SUB", "SHA", "SHL"};
std::vector<std::string> cmpops = {"CMPLT", "CMPLE", "-", "CMPEQ", "CMPLTU", "CMPLEU", "-", "-"};

std::vector<std::pair<std::string,int>> tworegops = {
    { "ADDI", 0 },
    { "LD", 1 },
    { "ST", 2 },
    { "LDB", 1 },
    { "STB", 2 },
    { "JALR", 3 }
};

std::vector<std::pair<std::string,int>> one_0_regops = {
    { "BZ", 0 },
    { "MOVI", 0 },
    { "IN", 0 },
};

std::vector<std::pair<std::string,int>> one_1_regops = {
    { "BNZ", 0 },
    { "MOVHI", 0 },
    { "OUT", 1 }
};

std::string formatError(std::string err, std::string instr){
    return "ERROR: " + err + " " + instr;
}

bool strValid(std::string str){
    return str != "" || str.find_first_not_of(' ') != std::string::npos;
}

void splitString(std::string str, std::vector<std::string>& argVec, std::string delimiter){
    int pos = 0;
    std::string token;
    // Separate args
    while((pos = str.find(delimiter)) != std::string::npos){
        token = str.substr(0, pos);

        if(strValid(token)) argVec.push_back(token);

        str.erase(0, pos + delimiter.length());
    }

    if (strValid(str)) argVec.push_back(str);
}

unsigned short int assemble (std::string line, bool& error, std::string& errorMsg){
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
            errorMsg = formatError(_MISSING_OPERAND_ERROR, instr);
            error = true;
            return 1;
        }
        if(instr != "NOT" && argVec.size() < 3){
            errorMsg = formatError(_MISSING_OPERAND_ERROR, instr);
            error = true;
            return 1;
        }

        std::bitset<3> regD (argVec[0][1]);
        std::bitset<3> regA (argVec[1][1]);
        std::bitset<3> regB;

        if(instr == "NOT"){
            regB = std::bitset<3> (0);
        }else{
            std::cout << "I am gonna do the THING" << std::endl;
            regB = std::bitset<3> (argVec[2][1]);
            std::cout << "Did I fail, son" << std::endl;

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
        if (argVec.size() < 3) {
            errorMsg = formatError(_MISSING_OPERAND_ERROR, instr);
            error = true;
            return 1;
        }

        std::bitset<6> N;
        std::bitset<3> regA;
        std::bitset<3> regBD; // B OR D

        std::vector<std::string> splitArgs;

        switch (order)
        {
            case 0:
                regBD = std::bitset<3>(argVec[0][1]);
                regA = std::bitset<3>(argVec[1][1]);
                try {
                    N = std::bitset<6>(std::stoi(argVec[2]));
                }
                catch (std::invalid_argument err){
                    error = true;
                    errorMsg = formatError(_INVALID_IMMEDIATE_ERROR, instr);
                    return 2;
                }
                break;
            case 1:
                regBD = std::bitset<3>(argVec[0][1]);
                splitString(argVec[1], splitArgs, "(");

                try{
                    N = std::bitset<6>(std::stoi(splitArgs[0]));
                } catch (std::invalid_argument err){
                    error = true;
                    errorMsg = formatError(_INVALID_IMMEDIATE_ERROR, instr);
                    return 2;
                }
                regA = std::bitset<3>(splitArgs[1][1]);
                break;
            case 2:
                regBD = std::bitset<3>(argVec[1][1]);
                splitString(argVec[0], splitArgs, "(");

                try{
                    N = std::bitset<6>(std::stoi(splitArgs[0]));
                } catch (std::invalid_argument err){
                    error = true;
                    errorMsg = formatError(_INVALID_IMMEDIATE_ERROR, instr);
                    return 2;
                }
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
        if (argVec.size() < 2) {
            errorMsg = formatError(_MISSING_OPERAND_ERROR, instr);
            error = true;
            return 1;
        }

        std::bitset<8> N;
        std::bitset<3> regAD;
        std::bitset<1> nextInstr; // B OR D

        std::vector<std::string> splitArgs;

        switch (order)
        {
            case 0:
                regAD = std::bitset<3>(argVec[0][1]);
                nextInstr = std::bitset<1>(f.to_ulong());
                try{
                    N = std::bitset<8>(std::stoi(argVec[1]));
                } catch (std::invalid_argument err){
                    error = true;
                    errorMsg = formatError(_INVALID_IMMEDIATE_ERROR, instr);
                    return 2;
                }
                break;
            case 1:
                regAD = std::bitset<3>(argVec[1][1]);
                nextInstr = std::bitset<1>(f.to_ulong());

                try{
                    N = std::bitset<8>(std::stoi(argVec[0]));
                } catch (std::invalid_argument err){
                    error = true;
                    errorMsg = formatError(_INVALID_IMMEDIATE_ERROR, instr);
                    return 2;
                }
                break;
        }

        debug("AD", regAD, 2);
        debug("N", N, 2);
        debug("NextInstr", nextInstr, 2);

        std::bitset<16> encInstr(op.to_string() + regAD.to_string() + nextInstr.to_string() + N.to_string());
        unsigned short int result = encInstr.to_ulong();

        debug("Encoded", encInstr, 1, false);
        debugHex(result, 1);
        
        return result;

    }else{
        errorMsg = formatError(_UNKNOWN_INSTRUCTION_ERROR, instr);
        error = true;
        return 3;
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

    // This will be probably replaced by a better handler
    // One ZERO register format INS REGA, REGB/D, N
    for (auto const& [key, val] : one_0_regops)
    {
        if(instr == key) {
            op = i;
            f = 0;
            order = val;
            return 1;
        }
        i++;
    }
    
    i -= one_0_regops.size();

   // One ONE register format INS REGA, REGB/D, N
    for (auto const& [key, val] : one_1_regops)
    {
        if(instr == key) {
            op = i;
            f = 1;
            order = val;
            return 1;
        }
        i++;
    }
 

    // One register format INS REGA, N
    return -1;
}
