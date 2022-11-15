#include <iostream>
#include <fstream>
#include <string>

#include "headers/strings.h"
#include "headers/params.h"
#include "headers/assembler.h"
#include "headers/utils.h"
#include "headers/globals.h"

void handleFlag(char const flag){
    switch (flag)
    {
        case 'h':
            std::cout << _WELCOME << " v" << _VERSION << std::endl;
            break;
        case 'v':
            __VERBOSE = true;
            break;
    }
}

void handleInput(char const* path){
    std::cout << "Opening " << path << std::endl;

    std::string line;
    std::ifstream file (path);

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            assemble(line);
        }
        file.close();
    }
    else std::cout << _FILEERROR; 
}
