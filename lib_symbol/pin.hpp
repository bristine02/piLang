#pragma once

#include <vector>
#include <string>
#include "location.hpp"
using namespace std;

class Pin
{
    public:
        Location rel_location;
        //float pin_length;
        string pin_name;
        string wire_name;
        unsigned int pin_num;

    public:
        Pin();
        ~Pin(){};

};