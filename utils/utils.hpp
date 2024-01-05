#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Utils
{
public:
    static vector<string> split_str(string &str, char delim);
    static vector<string> split_str_maintain_str_literals(string &str, char delim);
    static vector<string> split_str(string &str, string delim);
    static void remove_intances_of_char(string &str, char c);
    static size_t find_closing(const string& str, size_t opening_idx, char opening_delim, char closing_delim);
    static string generate_pseudo_uuid_from_str(const string& str);
    static bool is_delimeter(char c);
    static bool is_valid_name_char(char c);
    static bool is_valid_name_start(char c);

    Utils() = delete;
    ~Utils() = delete;
};


