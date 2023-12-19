#pragma once
#include <string>
#include <cstdint>
#include "../utils/utils.hpp"

using namespace std;


class LibField
{
public:
    string field_type;
    string text;
    int16_t pos_x;
    int16_t pos_y;
    int16_t dimension;
    char visibility;
    char h_justify;
    char v_justify;
    char italic;
    char bold;
    // ommitting "name" for now


public:
    LibField(string field_str);
    ~LibField();

protected:
    void parse(string field_str);
};



