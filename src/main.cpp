#include "headers/params.h"
#include "headers/globals.h"

#include <string>

int __VERBOSITY = 0;
bool __INLINE = false;
std::string __OUTPATH = "out.bin";

int main(int argc, char const *argv[])
{
    const char* pathIn;

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'o'){ // Output is a special case (parameter not flag)
                __OUTPATH = argv[++i];
            }
            else handleFlag(argv[i][1]);
            
        } 
        else pathIn = argv[i]; // We save later to execute after setting all the flags so order doesn't matter
    }

    handleInput(pathIn);
    return 0;
}