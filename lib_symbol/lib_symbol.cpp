#include "lib_symbol.hpp"


LibSymbol::LibSymbol(string& kicad_sym_str, LibInstance& lib_inst)
{
    this->lib_instance = lib_inst;

    // Find and construct all properties
    /* sample property:
            (property "Reference" "R" (at 2.032 0 90)
                (effects (font (size 1.27 1.27)))
            )
    */
    size_t current_idx = 0;
    size_t found = 0;
    while ((found = kicad_sym_str.find("(property", current_idx)) != string::npos)
    {
        Property prop;

        // construct property location
        current_idx = found;
        size_t prop_end = Utils::find_closing(kicad_sym_str, found, '(', ')');
        size_t prop_at = kicad_sym_str.find("(at", current_idx);
        size_t loc_end = Utils::find_closing(kicad_sym_str, prop_at, '(', ')');
        string loc_str = kicad_sym_str.substr(prop_at + 1, loc_end - (prop_at + 1));
        vector<string> loc = Utils::split_str(loc_str, ' ');

        //TODO: Better error reporting
        if(loc.size() < 4) {cout<<"ERROR: Malformatted property location"<<endl; break;}
        prop.location = Location(stof(loc.at(1)), stof(loc.at(2)), stof(loc.at(3)));

        //Get "type", "value"
        string prop_header_str = kicad_sym_str.substr(found, prop_at - found-1);
        vector<string> prop_header = Utils::split_str_maintain_str_literals(prop_header_str, ' ');
        //TODO: Better error reporting
        if(prop_header.size() != 3) {cout<<"ERROR: Malformatted property"<<endl; break;}
        prop.type = prop_header.at(1);
        prop.value = prop_header.at(2);

        // Get effects. substring from loc_end+1 to prop_end-1
        prop.effects = kicad_sym_str.substr(loc_end+1, prop_end - loc_end -2);

        // advance to next property or break if stuck
        if(prop_end == found || prop_end + 1 >= kicad_sym_str.length()) break;
        current_idx = prop_end + 1;

        cout<<"--------------------------Property--------------" <<endl;
        cout<< "Type: " << prop.type << " Value: " <<prop.value 
            << " At: x="<<prop.location.x << " y= " <<prop.location.x << " Rot= " <<prop.location.rot
            << "\n\t Effects" << prop.effects << endl;

    }
    


    this->location = Location(1,1, 10);
}

LibSymbol::~LibSymbol(){}


// void LibSymbol::setLibStr(string str)
// {
//     lib_Str = str;
// }

// string LibSymbol::getLibStr()
// {
//     return lib_Str;
// }