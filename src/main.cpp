#include "headers/params.h"

bool __VERBOSE = false;

int main(int argc, char const *argv[])
{
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-') handleFlag(argv[i][1]);
        else handleInput(argv[i]);
    }

    return 0;
}