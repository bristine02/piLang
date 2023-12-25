#pragma once

#include <string>
#include <cstdint>
#include <vector>

using namespace std;

typedef struct 
{
    uint16_t pin_num;
    string wire_name;
    
} PinConnection;


typedef struct 
{
    string lib_name;
    string kicad_lib_id;
    string base_uuid;
    string reference;
    vector<PinConnection> pin_connections;

} LibInstance;
