#include "kicad_io.hpp"
#include <fstream>
#include <sstream>
#include "../utils/utils.hpp"
#include "../lib_symbol/lib_symbol_strings.hpp" // for testing


KicadIO::KicadIO(string kicad_lib_dir, string output_dir)
            :kicad_lib_dir(kicad_lib_dir), output_dir(output_dir)
            {};

KicadIO::~KicadIO()
{
}

KicadIOState KicadIO::create_symbol(LibInstance lib_instance)
{
    vector<string> split_lib_id = Utils::split_str(lib_instance.kicad_lib_id, ':');
    if(split_lib_id.size() !=2) 
    {
        cout<<"ERROR: "<< lib_instance.kicad_lib_id <<" is not a valid kicad library ID" <<endl;
        return KicadIOState::ERROR;
    }

    KicadSym kicad_sym;
    bool exists_already = false;

    for(auto sym: this->libraries){
        if(sym.kicad_sym_name == split_lib_id.at(1)){
            kicad_sym = sym;
            exists_already = true;
            break;
        }    
    }

    if(!exists_already){
        auto status = this->get_kicad_sym_from_file(lib_instance, split_lib_id, kicad_sym);
        if(status == KicadIOState::SUCCESS) {
            this->libraries.push_back(kicad_sym);
        }
        else return status;
    }
  
    LibSymbol ls;
    bool success = LibSymbol::create(kicad_sym.kicad_sym_str, lib_instance, ls);

    if(!success){
        // The exact error would have been printed before this
        cout<<"Error encountered parsing instance " << lib_instance.reference 
        <<" of " << lib_instance.kicad_lib_id<<endl;
    }

    return KicadIOState::SUCCESS;
}


KicadIOState KicadIO::get_kicad_sym_from_file(LibInstance& lib_inst, vector<string>& split_lib_id, KicadSym& kicad_sym)
{

    string filename = this->kicad_lib_dir;
    filename.append(split_lib_id.at(0));
    filename.append(".kicad_sym");

    ifstream file;
    file.open(filename);
    if(!file.is_open())
    {
        cout<< "Could not open file: " << filename <<endl;
        return KicadIOState::ERROR_NO_KICAD_FILE;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string file_contents = buffer.str();
    // Search for symbol in file: e.g (symbol "GND"
    string query = "(symbol \"";
    query.append(split_lib_id.at(1));
    query.append("\"");
    size_t sym_start = file_contents.find(query);
    if(sym_start == string::npos) return KicadIOState::ERROR_NO_SYMBOL;
    size_t sym_end = Utils::find_closing(file_contents, sym_start, '(', ')');

    kicad_sym.kicad_sym_str = file_contents.substr(sym_start, sym_end +1 - sym_start);
    kicad_sym.kicad_sym_name = split_lib_id.at(1);

    //cout<<kicad_sym.kicad_sym_str<<endl;
    file.close();
    return KicadIOState::SUCCESS;
}
