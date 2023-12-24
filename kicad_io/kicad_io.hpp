#pragma once 
#include <string>
#include "../lib_symbol/lib_symbol.hpp"
#include "../compiler/token_group.hpp"
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

    public:
        KicadIO(string kicad_lib_dir, string output_dir);
        ~KicadIO();

        KicadIOState create_symbol(TokenGroup token_group);

    private:
        
};

