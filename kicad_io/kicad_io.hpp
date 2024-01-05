#pragma once 
#include <string>
#include "../lib_symbol/lib_symbol.hpp"
#include "../compiler/lib_instance.hpp"
#include <vector>
#include <optional>


using namespace std;

enum KicadIOState 
{   
    SUCCESS,
    ERROR_NO_KICAD_FILE,
    ERROR_NO_SYMBOL,
    ERROR
};


class KicadIO
{

    private:
        string kicad_lib_dir;
        string output_dir;
        vector<LibSymbol> lib_symbols;
        typedef struct
        {
            string kicad_sym_name;
            string kicad_sym_str;
        } KicadSym;
        vector<KicadSym> libraries;
        

    public:
        KicadIO(string kicad_lib_dir, string output_dir);
        ~KicadIO();

        KicadIOState create_symbol(LibInstance lib_instance);

    private:
        KicadIOState get_kicad_sym_from_file(LibInstance& lib_inst, vector<string>& split_lib_id, KicadSym& kicad_sym);
};

