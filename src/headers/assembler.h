#pragma once

#include <string>
#include <bitset>
#include <vector>

std::string formatError(std::string err, std::string instr);

bool strValid(std::string str);

void splitString(std::string str, std::vector<std::string>& argVec, std::string delimiter);

int getOpcode (std::string instr, std::bitset<4>& op, std::bitset<3>& f, int& order);

unsigned short int assemble (std::string line, bool& error, std::string& errorMsg);
