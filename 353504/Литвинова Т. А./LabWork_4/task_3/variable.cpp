#include <INCLUDES.h>

string Variable::getType()
{
    return _type;
}
string Variable::getName()
{
    return _name;
}
string Variable::getDefaultvalue()
{
    if(_defaultValue == "")
        return "-";
    return _defaultValue;
}
string Variable::getPositions()
{
    string tmp;
    for(size_t i = 0; i < _changingPositions.size();i++){
        stringstream ss,ss2;
        ss << _changingPositions[i].first;
        ss2 << _changingPositions[i].second;

        tmp += ss.str() + " " + ss2.str() + "\n";
    }
    return tmp;
}
string Variable::getVisibilityArea()
{
    if(_isGlobal)
        return "(GLOBAL)";
    return "(LOCAL)";
}
