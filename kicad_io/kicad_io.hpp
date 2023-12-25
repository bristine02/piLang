#pragma once 
#include <string>
#include "../lib_symbol/lib_symbol.hpp"
#include "../compiler/lib_instance.hpp"
#include <vector>

using namespace std;

enum KicadIOState 
{   
    SUCCESS,
    ERROR_NO_KICAD_FILE,

    ERROR
};


class KicadIO
{

    private:
        string kicad_lib_dir;
        string output_dir;
        vector<LibSymbol> lib_symbols;

    public:
        KicadIO(string kicad_lib_dir, string output_dir);
        ~KicadIO();

        KicadIOState create_symbol(LibInstance lib_instance);

    private:
        
};

