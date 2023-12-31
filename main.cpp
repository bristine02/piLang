#include "./compiler/compiler.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "./utils/utils.hpp"

using namespace std;


int main(int argc, char** argv)
{
    if(argc == 1)
    {
        cout<< "ERROR: No file provided" <<endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file;
    file.open(filename);
    if(!file.is_open())
    {
        cout<< "Could not open file" <<endl;
        return 1;
    } 

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    Compiler compiler;
    compiler.compile(buffer.str());

    string test_str = R"""(property "Reference" "R" (at 2.032 0 90)
      (effects (font (size 1.27 1.27)))
    )""";

    size_t end = Utils::find_closing(test_str, 47, '(', ')');

    //cout<< test_str.substr(47, 47+ end+1)<<endl;

    return 0;
}
