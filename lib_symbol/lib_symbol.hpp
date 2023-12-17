#pragma once
#include <string>
using namespace std;
class LibSymbol 
{
    protected:
        string lib_Str;
    

    public:
        LibSymbol();
        ~LibSymbol();
        string getLibStr();
        void setLibStr(string lib_Str);

};