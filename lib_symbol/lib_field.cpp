#include "lib_field.hpp"


LibField::LibField(){}
LibField::~LibField(){}

LibField::LibField(string field_str)
{
    this->parse(field_str);
}

void LibField::parse(string field_str)
{
    vector<string> fragments = split_str(field_str, ' ');

    // Fields (Fn) can be 9 fragments long or 10 fragments long if the "name" is included
    if (fragments.size() != 9 && fragments.size() != 10) // Malformed field
    {
        cout<< "Bad field: "<< field_str << endl;
        return;
    }

    try{
        this->field_type  = fragments.at(0);
        remove_intances_of_char(fragments.at(1), '\"');
        this->text        = fragments.at(1);
        this->pos_x       = stoi(fragments.at(2));
        this->pos_y       = stoi(fragments.at(3));
        this->dimension   = stoi(fragments.at(4));
        this->orientation = fragments.at(5).at(0);
        this->visibility  = fragments.at(6).at(0);
        this->h_justify   = fragments.at(7).at(0);
        this->v_justify   = fragments.at(8).at(0);
        this->italic      = fragments.at(8).at(1);
        this->bold        = fragments.at(8).at(2);
    } catch(...) { cout<< "Bad field: "<< field_str << endl; }
    
    //for(const auto frag:fragments) cout << frag << ", "; cout <<endl;

    return;
}


string LibField::get_s_expression()
{
    string property_name, property_value;
    float x, y, font_size;
    int16_t rot = 0; 

    if (this->field_type == "F0"){
        property_name = "Reference";
    }else if(this->field_type == "F1"){

        property_name = "Value";
    }else if(this->field_type == "F2"){

        property_name = "Footprint";
    }else if(this->field_type == "F3"){

        property_name = "Datasheet";
    }

    std::ostringstream oss;
    
    oss << "(property \"" << property_name << "\" \"" << property_value << "\" (at "
        << std::fixed << std::setprecision(2) << x << " " << y << " " << rot << ")\n"
        << "    (effects (font (size " << font_size << " " << font_size << ")))\n"
        << ")";

    return oss.str();
}


void LibField::test()
{
    // TODO: More tests

    string field_str = "F0 \"D\" 0 -100 50 H V L CNN";
    LibField* lib_field = new LibField(field_str);

    assert(lib_field->field_type  == "F0");
    assert(lib_field->text        == "D");
    assert(lib_field->pos_x       == 0);
    assert(lib_field->pos_y       == -100);
    assert(lib_field->dimension   == 50);
    assert(lib_field->orientation == 'H');
    assert(lib_field->visibility  == 'V');
    assert(lib_field->h_justify   == 'L');
    assert(lib_field->v_justify   == 'C');
    assert(lib_field->italic      == 'N');
    assert(lib_field->bold        == 'N');

}
