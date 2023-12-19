#pragma once 
#include <string>
#include "../lib_symbol/lib_symbol.hpp"


using namespace std;

class LibParser
{
public:
    LibParser();
    ~LibParser();

    LibSymbol parse(string lib_str);

};

LibParser::LibParser()
{
}

LibParser::~LibParser()
{
}
