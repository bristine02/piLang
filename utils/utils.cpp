#include "utils.hpp"


vector<string> Utils::split_str(string &str, char delim)
{
    vector<string> result;
    stringstream str_stream(str);
    string token;

    while(getline(str_stream, token, delim)){result.push_back(token);}
    return result;
}

vector<string> Utils::split_str_maintain_str_literals(string &str, char delim)
{
    size_t startPos = 0;
    size_t endPos = 0;
    string subStr;
    vector<string> result;

    while ((endPos = str.find(delim, endPos +1)) != string::npos)
    {
        if(str.at(startPos) == '"' && str.at(endPos - 1) != '"')
        {
            // Ignore splits in between " "
        }else
        {
            subStr = str.substr(startPos, endPos-startPos);
            result.push_back(subStr);
            startPos = endPos+1;
        }
    }
    // Get last substring (ignored by the while loop)
    subStr = str.substr(startPos, str.length()-startPos);
    result.push_back(subStr);

    return result; 
}


vector<string> Utils::split_str(string &str, string delim)
{
    size_t startPos = 0;
    size_t endPos = 0;
    string subStr;
    vector<string> result;

    while ((endPos = str.find(delim, startPos)) != string::npos)
    {
        subStr = str.substr(startPos, endPos-startPos);
        result.push_back(subStr);
        startPos = endPos+1;
    }
    // Get last substring (ignored by the while loop)
    subStr = str.substr(startPos, str.length()-startPos);
    result.push_back(subStr);
    return result;
}


void Utils::remove_intances_of_char(string &str, char c)
{
    string::iterator endPos = remove(str.begin(), str.end(), c);
    str.erase(endPos, str.end());
}

/**
 * Get the index of the closing char.
 * Example: given (ab ( cd ) ef (gh)) with opening_idx 4, and delims ( and )
 *          returns 9
 * NOTE: returns opening_idx for wrongly formatted string
*/
size_t Utils::find_closing(string& str, size_t opening_idx, char opening_delim, char closing_delim)
{
    size_t opened = 1;
    size_t current_idx = opening_idx + 1;

    while (opened !=0 && current_idx < str.length())
    {
        if(str.at(current_idx) == opening_delim) opened++;
        else if(str.at(current_idx) == closing_delim) opened--;

        if(opened > str.length()) return opening_idx;

        current_idx++;
    }
    
    if(opened == 0) return current_idx -1;
    else return opening_idx;
}


string Utils::generate_pseudo_uuid_from_str(const string& str)
{
    return "UNIMPLEMENTED";
}


bool Utils::is_delimeter(char c)
{
    string delims = ";.,()";
    size_t pos = delims.find(c);
    return pos != string::npos;
}

bool Utils::is_valid_name_char(char c)
{
    return  isalnum(c) || c == '_' || c == ':' || c=='+' || c=='-';
}

bool Utils::is_valid_name_start(char c)
{
    return isalpha(c) || c == '_';
}