#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "token.hpp"
#include "token_group.hpp"

#define LEXER_STATE_NO_ERROR 0
#define LEXER_STATE_ERROR 1
#define LEXER_STATE_END_OF_CONTENT 2

using namespace std;


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

