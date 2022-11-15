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
            __VERBOSITY = 2;
            break;
        case 'i':
            __INLINE = true;
            __VERBOSITY = 1;
            break;
    }
}

void handleInput(char const* path){
    if(__INLINE){
        assemble(path);
    }else{
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
}
