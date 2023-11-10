#pragma once
#include <string>

#define LEXER_STATE_NO_ERROR 0
#define LEXER_STATE_ERROR 1
#define LEXER_STATE_END_OF_CONTENT 2

using namespace std;


enum TokenType
{
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_NAME,
    TOKEN_TYPE_LIB,
    TOKEN_TYPE_LIB_INSTANCE,
    TOKEN_TYPE_OPEN_PAREN,
    TOKEN_TYPE_CLOSING_PAREN,
    TOKEN_TYPE_PIN_NAME,
    TOKEN_TYPE_SEMI_COLON,
    TOKEN_TYPE_DOT,
    TOKEN_TYPE_COMMA
};  

string token_type_name(TokenType token_type);


typedef struct
{
    TokenType token_type;
    char* value_ptr;  // Pointer to start of this value in the Lexer content.
                        // prevents duplicating strings
    size_t value_len;   // Length of token value
} Token;


// typedef struct
// {
//     string* content;
//     size_t content_len;
//     size_t cursor;
//     size_t line;
// } Lexer;

class Lexer
{
protected:
    string content;
    size_t content_len;
    size_t cursor;
    size_t line;
public:
    Lexer(const string& content);
    int lex_next(Token* token);

    ~Lexer(){};
};

