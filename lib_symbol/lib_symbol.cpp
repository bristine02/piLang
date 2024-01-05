#include "lib_symbol.hpp"


LibSymbol::LibSymbol(){}

LibSymbol::~LibSymbol(){}

bool LibSymbol::create(string& kicad_sym_str, LibInstance& lib_inst, LibSymbol& lib_sym_out)
{
    lib_sym_out.lib_instance = lib_inst;

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
        bool success = LibSymbol::find_and_parse_location(kicad_sym_str, found, prop.location, &prop_at, &loc_end);
        //TODO: Better error reporting
        if(!success) {
            cout<<"ERROR: Malformatted property location"<<endl;
            return false;
        }

        //Get "type", "value"
        size_t prop_end = Utils::find_closing(kicad_sym_str, found, '(', ')');
        string prop_header_str = kicad_sym_str.substr(found, prop_at - found-1);
        vector<string> prop_header = Utils::split_str_maintain_str_literals(prop_header_str, ' ');
        //TODO: Better error reporting
        if(prop_header.size() != 3) {
            cout<<"ERROR: Malformatted property"<<endl;
            return false;
        }
        prop.type = prop_header.at(1);
        prop.value = prop_header.at(2);

        // Get effects. substring from loc_end+1 to prop_end-1
        prop.effects = kicad_sym_str.substr(loc_end+1, prop_end - loc_end -2);

        // advance to next property or break if stuck
        if(prop_end == found || prop_end + 1 >= kicad_sym_str.length()) break;
        current_idx = prop_end + 1;

        lib_sym_out.properties.push_back(prop);

        /*
        cout<<"--------------------------Property--------------" <<endl;
        cout<< "Type: " << prop.type << " Value: " <<prop.value 
            << " At: x="<<prop.location.x << " y= " <<prop.location.x << " Rot= " <<prop.location.rot
            << "\n\t Effects" << prop.effects << endl;
        */
    }
    
    // Location not yet decided so initializing to the center
    lib_sym_out.location = Location(0, 0, 0);

    // find and construct pins
    while ((found = kicad_sym_str.find("(pin", current_idx)) != string::npos)
    {
        current_idx = found;
        Pin pin;
        bool success = LibSymbol::find_and_parse_location(kicad_sym_str, found, pin.rel_location);
        //TODO: Better error reporting
        if(!success) {
            cout<<"ERROR: Malformatted pin location"<<endl;
            return false;
        }

        size_t pin_num_start = kicad_sym_str.find("(number", current_idx);
        if(pin_num_start == string::npos){
            cout<<"ERROR: Malformatted pin number"<<endl;
            return false;
        }
        pin_num_start += 9; // add length of '(number "' Sample format: (number "21" (effects ....
        size_t pin_num_end = kicad_sym_str.find("\"", pin_num_start);
        if(pin_num_end == string::npos){
            cout<<"ERROR: Malformatted pin number"<<endl;
            return false;
        }
        
        pin.pin_num = stoi(kicad_sym_str.substr(pin_num_start, pin_num_end - pin_num_start));

        for(auto pin_con:lib_sym_out.lib_instance.pin_connections)
        {
            if(pin_con.pin_num == pin.pin_num){
                pin.wire_name = pin_con.wire_name;
                pin.isConnected = true;
                break;
            }
        }

        size_t pin_name_start = kicad_sym_str.find("(name", current_idx);
        if(pin_name_start == string::npos){
            cout<<"ERROR: Malformatted pin name"<<endl;
            return false;
        }
        pin_name_start += 7; // add length of '(name "' Sample format: (name "mypin" (effects ....
        size_t pin_name_end = kicad_sym_str.find("\"", pin_name_start);
        if(pin_name_end == string::npos){
            cout<<"ERROR: Malformatted pin name"<<endl;
            return false;
        }
        pin.pin_name = kicad_sym_str.substr(pin_name_start, pin_name_end - pin_name_start);

        /*
        cout<< "----------------Pin----------------"<<endl;
        cout<< "name: " << pin.pin_name << " Num: " << pin.pin_num 
            << " wire name: " << (!pin.wire_name.empty()? pin.wire_name : "NOT CONNECTED") << endl;
        */
        lib_sym_out.pins.push_back(pin);
        current_idx = pin_num_end;
    }
    return true;
}

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