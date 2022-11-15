#include "headers/params.h"
#include "headers/globals.h"
#include "headers/strings.h"

#include <iostream>

int __VERBOSITY = 0;
bool __INLINE = false;
std::string __OUTPATH = "out.bin";

int main(int argc, char const *argv[])
{
    const char* pathIn = "\0";

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'o'){ // Output is a special case (parameter not flag)
                if(i+1 < argc) __OUTPATH = argv[++i];
                else {
                    std::cout << _NO_INPUT_ERROR << std::endl;
                    return 1;
                }
            }
            else handleFlag(argv[i][1]);
            
        } 
        else pathIn = argv[i]; // We save later to execute after setting all the flags so order doesn't matter
    }

    if(pathIn != "\0") handleInput(pathIn);
    else handleFlag('h');

    return 0;
}