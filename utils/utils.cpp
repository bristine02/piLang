#include "utils.hpp"


vector<string> split_str(string &str, char delim)
{
    vector<string> result;
    stringstream str_stream(str);
    string token;

    while(getline(str_stream, token, delim)){result.push_back(token);}
    return result;
}


vector<string> split_str(string &str, string delim)
{
    size_t startPos = 0;
    size_t endPos = 0;
    string subStr;
    vector<string> result;

    while ((endPos = str.find(delim, startPos)) != string::npos)
    {
        subStr = str.substr(startPos, endPos);
        result.push_back(subStr);
        startPos = endPos;
    }

    return result; 
}


void remove_intances_of_char(string &str, char c)
{
    string::iterator endPos = remove(str.begin(), str.end(), c);
    str.erase(endPos, str.end());
}