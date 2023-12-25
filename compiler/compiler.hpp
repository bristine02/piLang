#pragma once
#include "lexer.hpp"
#include "../kicad_io/kicad_io.hpp"
#include "lib_parser.hpp"
#include "lib_instance.hpp"
#include <optional>
#include <algorithm>


class Compiler
{
private:
    optional<Lexer> lexer;
    LibParser lib_parser;
    optional<KicadIO> kicad_io;


public:
    Compiler();
    ~Compiler();

    void compile(const string& program);
};

