#pragma once
#include <string>
#include <iostream>
#include "globals.h"

template <typename T>
void debug(std::string key, T value){
  if (__VERBOSE) std::cout << key << ": " << value << std::endl;
}