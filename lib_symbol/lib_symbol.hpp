#pragma once
#include <string>
#include "location.hpp"
#include "pin.hpp"
#include "../utils/utils.hpp"
#include "../compiler/lib_instance.hpp"
#include <iostream>
#include <optional>

using namespace std;

class LibSymbol 
{
    private:
        LibInstance lib_instance;
        Location location;
        vector<Pin> pins;

        typedef struct
        {
            Location location;
            string type;
            string value;
            string effects;
            string get_lib_inst_prop_str(Location& lib_inst_location);
        } Property;

        vector<Property> properties;

        //helpers
        bool find_and_parse_location(string& str, size_t start, Location& out_loc, 
                optional<size_t*> out_loc_start = nullopt, optional<size_t*> out_loc_end = nullopt);
        

    public:
        LibSymbol(string& kicad_sym_str, LibInstance& lib_inst);
        ~LibSymbol();
        // string getLibStr();
        // void setLibStr(string lib_Str);


};