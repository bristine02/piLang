#pragma once 
#include <string>
#include "../compiler/lib_instance.hpp"
#include "../compiler/token_group.hpp"
#include "../compiler/token.hpp"
#include <vector>
#include <optional>
#include <iostream>
#include <fstream>
// #include <jsoncpp/json/json.h>

using namespace std;

enum LibParserState 
{   
    PARSER_STATE_SUCCESS,
    ERROR_INVALID_INSTANCE,
    ERROR_UNKNOWN
};


class LibParser
{
    public:
        LibParserState state {LibParserState::PARSER_STATE_SUCCESS};

    public:
        LibParser();
        ~LibParser();

        optional<LibInstance> parse_lib_instance(TokenGroup& token_group, vector<Token>& tokens);

};

