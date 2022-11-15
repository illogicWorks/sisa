#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "globals.h"

template <typename T>
void debug(std::string key, T value, int verbosity, bool nl = true){
  if (__VERBOSITY >= verbosity){
    std::cout << key << ": " << value;
    if(nl) std::cout << std::endl;
  }
}

// Maybe this should not strictly be a template function becouse I will alyways pass it the same type, but I don't want more of this c++ include hell
template <typename T>
void debugHex(T value, int verbosity, bool nl = true){
  if (__VERBOSITY >= verbosity){
    std::cout << " (0x" << std::setfill('0') << std::setw(sizeof(T)*2) << std::hex << std::uppercase << value << std::dec << ')';
    if(nl) std::cout << std::endl;
  }
}