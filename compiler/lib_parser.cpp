#include "lib_parser.hpp"

LibParser::LibParser()
{
}

LibParser::~LibParser()
{
}

optional<LibInstance> LibParser::parse_lib_instance(TokenGroup& token_group, vector<Token>& tokens)
{
    LibInstance lib_instance;
    // First token in a token group is always the lib_name, and then next token is always the instance name [refernce]
    lib_instance.lib_name = tokens.at(token_group.tokens_start).get_value();
    lib_instance.reference = tokens.at(token_group.tokens_start + 1).get_value();

    Json::Value root;
    std::ifstream ifs;
    ifs.open("./config/pi_lib.json");

    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
    }else{
        lib_instance.base_uuid = root["PILIBS"][lib_instance.lib_name]["base_uuid"].asString();
        lib_instance.kicad_lib_id = root["PILIBS"][lib_instance.lib_name]["kicad_lib_id"].asString();
    }

    // find all pin names in token group, get their wire names and construct a connection
    for (size_t i = token_group.tokens_start + 2; i < token_group.tokens_start + token_group.tokens_length; i++)
    {
        Token token = tokens.at(i);

        if(token.token_type == TokenType::TOKEN_TYPE_PIN_NAME){
            PinConnection pin_con{0};
            if(tokens.at(i+2).token_type == TokenType::TOKEN_TYPE_WIRE_NAME){
                pin_con.wire_name = tokens.at(i + 2).get_value();
                pin_con.pin_num = stoi(token.get_value().substr(3)); // pin name format: pin# (e.g pin12)
                lib_instance.pin_connections.push_back(pin_con);
            }else{
                cout<< "Expecting a wire name, got "<<tokens.at(i+2).get_value()<<endl;
            }
        }
    }
    
    return lib_instance;
}
