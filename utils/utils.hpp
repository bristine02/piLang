#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> split_str(string &str, char delim);

vector<string> split_str(string &str, string delim);

void remove_intances_of_char(string &str, char c);

size_t find_closing(string& str, size_t opening_idx, char opening_delim, char closing_delim);
