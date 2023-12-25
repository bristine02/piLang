#include "kicad_io.hpp"

KicadIO::KicadIO(string kicad_lib_dir, string output_dir)
            :kicad_lib_dir(kicad_lib_dir), output_dir(output_dir)
            {};

KicadIO::~KicadIO()
{
}

KicadIOState KicadIO::create_symbol(LibInstance lib_instance)
{
    return KicadIOState();
}
