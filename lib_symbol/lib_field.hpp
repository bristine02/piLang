#pragma once
#include <string>
#include <cstdint>
#include <iostream>
#include "../utils/utils.hpp"

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

using namespace std;


class LibField
{
public:
    string field_type;
    string text;
    int16_t pos_x;
    int16_t pos_y;
    int16_t dimension;
    char orientation;
    char visibility;
    char h_justify;
    char v_justify;
    char italic;
    char bold;
    // ommitting "name" for now


public:
    LibField(string field_str);
    LibField();
    ~LibField();

    void parse(string field_str);
    void test();

};



