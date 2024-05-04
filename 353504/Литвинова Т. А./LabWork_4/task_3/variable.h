#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include <vector>
#include<sstream>
using namespace std;
class Variable
{
public:
    Variable(){};
    Variable(string type, string name, vector<pair<int,int>> changingPositions, string defaultValue, bool isGlobal = false)
        : _type(std::move(type)), _name(std::move(name)), _defaultValue(std::move(defaultValue)),
        _changingPositions(std::move(changingPositions)), _isGlobal(isGlobal) {}
    string getType();
    string getName();
    string getDefaultvalue();
    string getPositions();
    string getVisibilityArea();

private:
    string _type;
    string _name;
    string _defaultValue;
    vector<pair <int,int>> _changingPositions;
    bool _isGlobal;
};
#endif // VARIABLE_H
