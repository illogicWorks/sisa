#include <iostream>
#include <fstream>
#include <string>

#include "headers/strings.h"
#include "headers/params.h"
#include "headers/assembler.h"

using namespace std;

bool verbose = false;

void handleFlag(char const flag){
    switch (flag)
    {
        case 'h':
            cout << _WELCOME << " v" << _VERSION << endl;
            break;
        case 'v':
            verbose = true;
            break;
    }
}

void handleInput(char const* path){
    cout << "Opening " << path << endl;

    string line;
    ifstream file (path);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if(verbose){
                cout << line << '\n';
            }
            
            assemble(line);

        }
        file.close();
    }
    else cout << _FILEERROR; 
}
