#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <bitset>

int getOpcode (std::string instr, std::bitset<4>& op, std::bitset<3>& f);

unsigned short int assemble (std::string line);
