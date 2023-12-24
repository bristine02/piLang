#pragma once 
#include <string>
#include "../compiler/lib_instance.hpp"
#include "../compiler/token_group.hpp"
#include <vector>
#include <optional>

using namespace std;

enum LibParserState 
{   
    SUCCESS,
    ERROR_INVALID_INSTANCE,
    ERROR_UNKNOWN
};


class LibParser
{
    public:
        LibParserState state {LibParserState::SUCCESS};

    public:
        LibParser();
        ~LibParser();

        optional<LibInstance> parse_lib_instance(TokenGroup token_group);

};

