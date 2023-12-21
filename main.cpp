#include "./lib_symbol/lib_symbol.hpp"
#include "./compiler/lexer.hpp"
#include "./lib_symbol/lib_field.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

vector<string> splitString(string* str, string delimiter);
void removeAllChars(string* str, char c);


int main(int argc, char** argv)
{
    if(argc == 1)
    {
        cout<< "ERROR: No file provided" <<endl;
        return 1;
    }

    // LibSymbol libSymR;
    // libSymR.setLibStr(LIB_R);
    // LibSymbol libSym3V3;
    // libSymR.setLibStr(LIB_3V3);
    // LibSymbol libSymGND;
    // libSymR.setLibStr(LIB_GND);


    string filename = argv[1];
    ifstream file;
    file.open(filename);
    if(!file.is_open())
    {
        cout<< "Could not open file" <<endl;
        return 1;
    } 

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    // cout<<buffer.str()<<endl;
    Lexer lexer = Lexer(buffer.str());
    lexer.tokenize();
    
    // for (Token token: lexer.tokens)
    // {
    //     string token_value(token.value_ptr, token.value_len);
    //     std::cout << token_type_name(token.token_type) << ": " << token_value <<endl;
    // }

    lexer.groupTokens();

    LibField lf;
    lf.test();
    

    return 0;
}
