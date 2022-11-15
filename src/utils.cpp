#include "headers/utils.h"

bool vrbs = false;

void setVerbose(){
  vrbs = true;
}

void debug(std::string key, std::string value){
  if (vrbs) std::cout << key << ": " << value << std::endl;
}

void debug(std::string key, int value){
  if (vrbs) std::cout << key << ": " << value << std::endl;
}



