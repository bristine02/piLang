#include "./compiler/compiler.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
    if(argc == 1)
    {
        cout<< "ERROR: No file provided" <<endl;
        return 1;
    }

    // LibSymbol libSymR;
    // libSymR.setLibStr(LIB_R);
    // LibSymbol libSym3V3;
    // libSymR.setLibStr(LIB_3V3);
    // LibSymbol libSymGND;
    // libSymR.setLibStr(LIB_GND);


    string filename = argv[1];
    ifstream file;
    file.open(filename);
    if(!file.is_open())
    {
        cout<< "Could not open file" <<endl;
        return 1;
    } 

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    Compiler compiler;
    compiler.compile(buffer.str());
    
    return 0;
}
