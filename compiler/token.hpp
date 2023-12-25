#pragma once
#include <cstddef>
using namespace std;

enum TokenType
{

    // Some token types are not currently being used
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_NAME,  // Generic for all "word" tokens
    TOKEN_TYPE_LIB,
    TOKEN_TYPE_LIB_INSTANCE,
    TOKEN_TYPE_WIRE,
    TOKEN_TYPE_WIRE_NAME,
    TOKEN_TYPE_OPEN_PAREN,
    TOKEN_TYPE_CLOSING_PAREN,
    TOKEN_TYPE_PIN_NAME,
    TOKEN_TYPE_SEMI_COLON,
    TOKEN_TYPE_DOT,
    TOKEN_TYPE_COMMA,
    TOKEN_TYPE_MODULE,
    TOKEN_TYPE_MODULE_NAME,
    TOKEN_TYPE_ENDMODULE,
    TOKEN_TYPE_NONE 
};

typedef struct
{
    TokenType token_type;
    char* value_ptr;  // Pointer to start of this value in the Lexer content.
                        // prevents duplicating strings
    size_t value_len;   // Length of token value

    string get_value(){ return string(value_ptr, value_len); }
} Token;
