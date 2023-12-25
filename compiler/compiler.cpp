#include "compiler.hpp"

Compiler::Compiler()
{
}

Compiler::~Compiler()
{
}

void Compiler::compile(const string& program)
{
    this->lexer = Lexer(program);
    this->lexer.value().tokenize();
    this->lexer.value().groupTokens();

    for(auto token_group: this->lexer.value().token_groups)
    {
        if(token_group.tokenGroupType == TokenGroupType::TOKEN_GROUP_LIB_INSTANCE
            && this->lexer.value().tokens.at(token_group.tokens_start).token_type == TokenType::TOKEN_TYPE_LIB){

            optional<LibInstance> lib_inst = this->lib_parser.parse_lib_instance(token_group, this->lexer.value().tokens);
            if (!lib_inst.has_value()) cout<< "ERROR: couldn't parse lib instance" << endl;

            else
            {
                
            }

            {
                // cout<<lib_inst.value().lib_name 
                // <<", Ref: "<<lib_inst.value().reference
                // <<", UUID: "<<lib_inst.value().base_uuid
                // <<", LIB_ID: "<<lib_inst.value().kicad_lib_id 
                // <<" Last wire name: " << lib_inst.value().pin_connections.back().wire_name
                // <<" Last pinnum: " << lib_inst.value().pin_connections.back().pin_num <<endl;
            }
        }
        
    }
}