#pragma once
#include <string>
#include <iostream>
#include "globals.h"

template <typename T>
void debug(std::string key, T value, int verbosity){
  if (__VERBOSITY >= verbosity) std::cout << key << ": " << value << std::endl;
}