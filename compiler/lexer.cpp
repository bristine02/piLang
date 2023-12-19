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
        return "semi-colon";
    case TOKEN_TYPE_DOT:
        return "dot";
    case TOKEN_TYPE_COMMA:
        return "comma";
    case TOKEN_TYPE_OPEN_PAREN:
        return "open-paren";
    case TOKEN_TYPE_CLOSING_PAREN:
        return "closing-paren";
    case TOKEN_TYPE_LIB:
        return "lib";
    case TOKEN_TYPE_LIB_INSTANCE:
        return "lib-instance";
    case TOKEN_TYPE_WIRE:
        return "wire";
    case TOKEN_TYPE_WIRE_NAME:
        return "wire-name";
    case TOKEN_TYPE_MODULE:
        return "module";
    case TOKEN_TYPE_MODULE_NAME:
        return "module-name";
    case TOKEN_TYPE_ENDMODULE:
        return "endmodule";
    case TOKEN_TYPE_PIN_NAME:
        return "pin-name";
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
    this->potential_next_token_types = {TOKEN_TYPE_MODULE};
}

int Lexer::lex_next(Token* token)
{
    // TODO: Track code line for error reporting

    // Skip white spaces
    while ((this->content[this->cursor] == ' ' || this->content[this->cursor] == '\n' 
            || this->content[this->cursor] == '\r') && (this->cursor < this->content_len))
    {
        if(this->content[this->cursor] == '\n') this->line++;
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
            this->potential_next_token_types = {TOKEN_TYPE_WIRE, TOKEN_TYPE_LIB, TOKEN_TYPE_ENDMODULE};
            break;
        case '.':
            token->token_type = TOKEN_TYPE_DOT;
            this->potential_next_token_types = {TOKEN_TYPE_PIN_NAME};
            break;
        case ',':
            token->token_type = TOKEN_TYPE_COMMA;
            this->potential_next_token_types = {TOKEN_TYPE_DOT};
            break;
        case '(':
            token->token_type = TOKEN_TYPE_OPEN_PAREN;
            this->potential_next_token_types = {TOKEN_TYPE_CLOSING_PAREN, TOKEN_TYPE_DOT, TOKEN_TYPE_WIRE_NAME};
            break;
        case ')':
            token->token_type = TOKEN_TYPE_CLOSING_PAREN;
            this->potential_next_token_types = {TOKEN_TYPE_SEMI_COLON, TOKEN_TYPE_COMMA, TOKEN_TYPE_CLOSING_PAREN};
            break;
        
        default:  // Should never happen
            cout<< "Unrecognized token: " << this->content[this->cursor] << endl;
            break;
        }

        this->cursor++;
        return LEXER_STATE_NO_ERROR;
    }

    else if (is_valid_name_start(this->content[this->cursor]))
    {
        token->token_type = TOKEN_TYPE_NAME;
        while (is_valid_name_char(this->content[this->cursor]) && (this->cursor < this->content_len))
        {
            this->cursor++;
            token->value_len++;
        }
        return LEXER_STATE_NO_ERROR;
    }
    else { cout<< "Unrecognized token: " << this->content[this->cursor] << endl; }
  
  return LEXER_STATE_ERROR;
}

int Lexer::update_token_type(Token* token, Token* prev_token)
{
    string token_str = this->get_token_value(token);

    if (token_str == "module")
    {
        token->token_type = TOKEN_TYPE_MODULE;
        this->potential_next_token_types = {TOKEN_TYPE_MODULE_NAME};
    }
    else if(token_str == "endmodule")
    {
        token->token_type = TOKEN_TYPE_ENDMODULE;
        this->potential_next_token_types = {TOKEN_TYPE_NONE};
    }
    else if(token_str == "wire")
    {
        token->token_type = TOKEN_TYPE_WIRE;
        this->potential_next_token_types = {TOKEN_TYPE_WIRE_NAME};
    }
    else // Predictable token types
    {
        // TODO: add support for module inputs and outputs

        // At least one token has been tokenized before this point
        if (prev_token == nullptr) return LEXER_STATE_ERROR;
        
        switch (prev_token->token_type)
        {
        case TOKEN_TYPE_MODULE:
            token->token_type = TOKEN_TYPE_MODULE_NAME;
            this->potential_next_token_types = {TOKEN_TYPE_OPEN_PAREN};
            break;
        case TOKEN_TYPE_WIRE:
            token->token_type = TOKEN_TYPE_WIRE_NAME;
            this->potential_next_token_types = {TOKEN_TYPE_SEMI_COLON};
            break;
        case TOKEN_TYPE_SEMI_COLON:
            token->token_type = TOKEN_TYPE_LIB;  // wire taken care of already above
            this->potential_next_token_types = {TOKEN_TYPE_LIB_INSTANCE};
            break;
        case TOKEN_TYPE_LIB: 
            token->token_type = TOKEN_TYPE_LIB_INSTANCE;
            this->potential_next_token_types = {TOKEN_TYPE_OPEN_PAREN};
            break;
        case TOKEN_TYPE_DOT:
            token->token_type = TOKEN_TYPE_PIN_NAME;
            this->potential_next_token_types = {TOKEN_TYPE_OPEN_PAREN};
            break;
        case TOKEN_TYPE_OPEN_PAREN:
            token->token_type = TOKEN_TYPE_WIRE_NAME;
            this->potential_next_token_types = {TOKEN_TYPE_CLOSING_PAREN};
            break;
        default:
            break;
        }
    }

    return LEXER_STATE_NO_ERROR;
}


void Lexer::tokenize()
{
    int lex_status = LEXER_STATE_NO_ERROR;
    while (lex_status == LEXER_STATE_NO_ERROR)
    {
        Token t;
        vector<TokenType> expected_token_types = this->potential_next_token_types;
        lex_status = this->lex_next(&t);
        if(lex_status == LEXER_STATE_NO_ERROR)
        {
            // Make token type more specific is it's a word
            if (t.token_type == TOKEN_TYPE_NAME) 
            {
                Token *prev_token = nullptr;
                if(this->tokens.size() > 0) prev_token = &(this->tokens.back());
                int status = this->update_token_type(&t, prev_token);
                if (status == LEXER_STATE_ERROR)
                {
                    cout<< "ERROR: Unexpected token on line " << this->line << ", near \"" << this->get_token_value(&t) << "\"\n";
                    break;
                }
            }

            if (!this->is_expected_token_type(&t, expected_token_types))
            {
                cout<< "ERROR: Unexpected token \"" << this->get_token_value(&t) << "\" on line " << this->line << endl;
                break;
            }
            
            this->tokens.push_back(t);
        }
        else if(lex_status == LEXER_STATE_ERROR)
        {
            cout<< "ERROR: Unexpected token on line " << this->line <<endl;
            break;
        }
    }   
}

void Lexer::groupTokens()
{
    if(this->tokens.size() == 0) return;

    if(this->tokens.at(0).token_type != TokenType::TOKEN_TYPE_MODULE)
    {
        cout<< "Circuit definition must start with \"module\""<<endl;
        return;
    }

    size_t token_idx = 0;
    while (token_idx < this->tokens.size())
    {
        TokenGroup tGroup;
        Token token = this->tokens.at(token_idx);
        cout<< token_type_name(token.token_type)<<endl;
        if(token.token_type == TokenType::TOKEN_TYPE_MODULE)
        {
            tGroup.tokenGroupType = TokenGroupType::TOKEN_GROUP_MODULE_HEADER;
        } 
        else if (token.token_type == TokenType::TOKEN_TYPE_ENDMODULE)
        {
            tGroup.tokenGroupType = TokenGroupType::TOKEN_GROUP_MODULE_END;
        } 
        else
        {
            // All other tokens are currently classified as lib instances
            tGroup.tokenGroupType = TokenGroupType::TOKEN_GROUP_LIB_INSTANCE; 
        }

        // find end of token group (next ;)
        size_t idx = token_idx;
        while ((token_idx < this->tokens.size()) && (this->tokens.at(token_idx).token_type != TOKEN_TYPE_SEMI_COLON))
        {
            token_idx++;
        }

        tGroup.tokens_length = token_idx - idx;
        tGroup.tokens_start = idx;
        this->token_groups.push_back(tGroup);
        token_idx++;
    }
    cout<< "Grouping done. Groups: "<<this->token_groups.size()<<endl; 
}

bool Lexer::is_expected_token_type(Token* token, vector<TokenType> expected_token_types)
{
    return find(expected_token_types.begin(), expected_token_types.end(), token->token_type) != expected_token_types.end();
}

string Lexer::get_token_value(Token* t)
{
    string token_value(t->value_ptr, t->value_len);
    return token_value;
}