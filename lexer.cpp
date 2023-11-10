#include "lexer.hpp"
#include <iostream>


bool is_valid_name_start(char c)
{
    return isalpha(c) || c == '_';
}

bool is_valid_name_char(char c)
{
    return isalnum(c) || c == '_';
}

string token_type_name(TokenType token_type)
{
    switch (token_type)
    {
    case TOKEN_TYPE_NAME:
        return "name";
    case TOKEN_TYPE_SEMI_COLON:
        return "semi colon";
    case TOKEN_TYPE_DOT:
        return "dot";
    case TOKEN_TYPE_COMMA:
        return "comma";
    case TOKEN_TYPE_OPEN_PAREN:
        return "open paren";
    case TOKEN_TYPE_CLOSING_PAREN:
        return "closing paren";
    default:
        return "Currently Unknown";
    }
}

bool is_delimeter(char c)
{
    string delims = ";.,()";
    size_t pos = delims.find(c);
    return pos != string::npos;
}


Lexer::Lexer(const string& content)
{
    
    this->content = content;
    this->content_len = content.length();
    this->cursor = 0;
    this->line = 0;
}

int Lexer::lex_next(Token* token)
{
    // Skip white spaces
    while ((this->content[this->cursor] == ' ' || this->content[this->cursor] == '\n') && (this->cursor < this->content_len))
    {
        this->cursor++;
    }

    // Stop if at end of content
    if (this->cursor >= this->content_len)
    {
        return LEXER_STATE_END_OF_CONTENT;
    }

    token->value_ptr = &(this->content[this->cursor]);
    token->value_len = 0;

    if (is_delimeter(this->content[this->cursor]))
    {
        token->value_len = 1;
        switch (this->content[this->cursor])
        {
        case ';':
            token->token_type = TOKEN_TYPE_SEMI_COLON;
            break;
        case '.':
            token->token_type = TOKEN_TYPE_DOT;
            break;
        case ',':
            token->token_type = TOKEN_TYPE_COMMA;
            break;
        case '(':
            token->token_type = TOKEN_TYPE_OPEN_PAREN;
            break;
        case ')':
            token->token_type = TOKEN_TYPE_CLOSING_PAREN;
            break;
        
        default:  // Should never happen
            break;
        }

        this->cursor++;
        return LEXER_STATE_NO_ERROR;
    }

    if (is_valid_name_start(this->content[this->cursor]))
    {
        token->token_type = TOKEN_TYPE_NAME;
        while (is_valid_name_char(this->content[this->cursor]) && (this->cursor < this->content_len))
        {
            this->cursor++;
            token->value_len++;
        }
        return LEXER_STATE_NO_ERROR;
    }
  
  return LEXER_STATE_ERROR;
}