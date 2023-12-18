#pragma once
#include <string>
#include <vector>
#include <algorithm>

#define LEXER_STATE_NO_ERROR 0
#define LEXER_STATE_ERROR 1
#define LEXER_STATE_END_OF_CONTENT 2

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

enum TokenGroupType
{
    TOKEN_GROUP_MODULE_HEADER,
    TOKEN_GROUP_LIB_INSTANCE,
    TOKEN_GROUP_MODULE_END
};

typedef struct
{
    TokenType token_type;
    char* value_ptr;  // Pointer to start of this value in the Lexer content.
                        // prevents duplicating strings
    size_t value_len;   // Length of token value
} Token;

typedef struct
{
    TokenGroupType tokenGroupType;
    size_t tokens_start; // Index of first token in token group.
    size_t tokens_length;      // number of tokens in token group
} TokenGroup;

string token_type_name(TokenType token_type);

class Lexer
{
protected:
    string content;
    size_t content_len;
    size_t cursor;
    size_t line;
    vector<TokenType> potential_next_token_types;

public:
    vector<Token> tokens;
    vector<TokenGroup> token_groups;

protected:
    int lex_next(Token* token);
    int update_token_type(Token* token, Token* prev_token);
    bool is_expected_token_type(Token* token, vector<TokenType> expected_token_types);

public:
    Lexer(const string& content);
    void tokenize();
    string get_token_value(Token* t);
    void groupTokens();

    ~Lexer(){};
};

