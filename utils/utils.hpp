#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> split_str(string &str, char delim);

vector<string> split_str(string &str, string delim);

void remove_intances_of_char(string &str, char c);