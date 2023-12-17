#include "utils.hpp"


vector<string> split_str(string &str, char delim)
{
    vector<string> result;
    stringstream str_stream(str);
    string token;

    while(getline(str_stream, token, delim)){result.push_back(token);}
    return result;
}