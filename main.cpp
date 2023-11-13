#include "lib_symbol.hpp"
#include "lib_symbol_strings.hpp"
#include "lexer.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

    LibSymbol libSymR;
    libSymR.setLibStr(LIB_R);
    LibSymbol libSym3V3;
    libSymR.setLibStr(LIB_3V3);
    LibSymbol libSymGND;
    libSymR.setLibStr(LIB_GND);


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
    
    for (Token token: lexer.tokens)
    {
        string token_value(token.value_ptr, token.value_len);
        std::cout << token_type_name(token.token_type) << ": " << token_value <<endl;
    }
    

    return 0;
}

void removeAllChars(string* str, char c)
{
    string::iterator endPos = remove(str->begin(), str->end(), c);
    str->erase(endPos, str->end());
}

vector<string> splitString(string* str, string delimiter)
{
    size_t startPos = 0;
    size_t endPos = 0;
    string subStr;
    vector<string> result;

    while ((endPos = str->find(delimiter, startPos)) != string::npos)
    {
        subStr = str->substr(startPos, endPos);
        result.push_back(subStr);
        startPos = endPos;
    }

    return result; 
}