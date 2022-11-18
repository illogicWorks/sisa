#include <iostream>
#include <fstream>
#include <iterator>
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
            std::cout << _USAGE << std::endl;
            std::cout << _FLAGS << std::endl;
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

int handleInput(char const* path){
    bool error = false;
    std::string errorMsg = "";
    int lineN = 1;
    if(__INLINE){
        assemble(path, error, errorMsg);
        if(error) std::cout << errorMsg << std::endl; // TODO ERROR HANDLING
    }else{
        std::cout << "Opening " << path << std::endl;

        std::string line;
        std::ifstream file (path);

        if (file.is_open())
        {
            std::ofstream oFile (__OUTPATH, std::ios::out | std::ios::binary);
            
            while (std::getline(file, line))
            {
                unsigned short int data = assemble(line, error, errorMsg);
                if (!error) oFile.write((char*) &data, sizeof(data));
                else {
                    std::cout << errorMsg << " at line " << lineN << std::endl;
                }
                lineN++;
            }
            file.close();
            oFile.close();

            if(!oFile.good()) std::cout << _FILE_WRITE_ERROR << std::endl;
        }
        else std::cout << _FILE_READ_ERROR << std::endl; 
    }

    return error;
}
