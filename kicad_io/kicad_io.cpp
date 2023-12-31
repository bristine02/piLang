#include "kicad_io.hpp"
#include "../lib_symbol/lib_symbol_strings.hpp" // for testing


KicadIO::KicadIO(string kicad_lib_dir, string output_dir)
            :kicad_lib_dir(kicad_lib_dir), output_dir(output_dir)
            {};

KicadIO::~KicadIO()
{
}

KicadIOState KicadIO::create_symbol(LibInstance lib_instance)
{
    LibSymbol ls = LibSymbol(LIB_R, lib_instance);

    return KicadIOState::SUCCESS;
}
