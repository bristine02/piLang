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
        size_t prop_at;
        size_t loc_end;
        bool success = this->find_and_parse_location(kicad_sym_str, found, prop.location, &prop_at, &loc_end);
        //TODO: Better error reporting
        if(!success) {cout<<"ERROR: Malformatted property location"<<endl; break;}

        //Get "type", "value"
        size_t prop_end = Utils::find_closing(kicad_sym_str, found, '(', ')');
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

        this->properties.push_back(prop);

        cout<<"--------------------------Property--------------" <<endl;
        cout<< "Type: " << prop.type << " Value: " <<prop.value 
            << " At: x="<<prop.location.x << " y= " <<prop.location.x << " Rot= " <<prop.location.rot
            << "\n\t Effects" << prop.effects << endl;

    }
    
    // Location not yet decided so initializing to the center
    this->location = Location(0, 0, 0);


}

LibSymbol::~LibSymbol(){}

bool LibSymbol::find_and_parse_location(string& str, size_t start, Location& out_loc, 
                optional<size_t*> out_loc_start, optional<size_t*> out_loc_end)
{
    size_t loc_start = str.find("(at", start);
    size_t loc_end = Utils::find_closing(str, loc_start, '(', ')');
    string loc_str = str.substr(loc_start + 1, loc_end - (loc_start + 1));
    vector<string> loc = Utils::split_str(loc_str, ' ');
    if(loc.size() < 4) {return false;}

    out_loc.x = stof(loc.at(1));
    out_loc.y = stof(loc.at(2)); 
    out_loc.rot = stof(loc.at(3));

    if(out_loc_start.has_value()) *(out_loc_start.value()) = loc_start;
    if(out_loc_end.has_value()) *(out_loc_end.value()) = loc_end;

    return true;
}


// void LibSymbol::setLibStr(string str)
// {
//     lib_Str = str;
// }

// string LibSymbol::getLibStr()
// {
//     return lib_Str;
// }