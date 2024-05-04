#include <INCLUDES.h>

string Functions::getName()
{
    return _functionName;
}

string Functions::getType()
{
    return _functionType;
}

string Functions::getPrototype()
{
    string args = "";
    for(auto i : _functionArgs){
        args += i + ", ";
    }

    return _functionType + " " + _functionName + " (" + args + ");";
}

string Functions::getOverloadsFunctions()
{
    string str;
    for(size_t i = 0; i < _overloadedFunctions.size(); i++){
        str += " " + _overloadedFunctions[i].getPrototype() + "\n";
    }
    return str;
}
