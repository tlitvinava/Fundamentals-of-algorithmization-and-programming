#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <vector>
using namespace std;
class Functions
{
public:
    Functions(){};
    Functions(string functionType, string functionName, vector<Functions> overloadedFunctions, vector<string> functionArgs)
        : _functionName(std::move(functionName)), _functionType(std::move(functionType)),
        _overloadedFunctions(std::move(overloadedFunctions)), _functionArgs(std::move(functionArgs)) {}

    Functions(string functionType, string functionName, vector<string> functionArgs)
        : _functionName(std::move(functionName)), _functionType(std::move(functionType)), _functionArgs(std::move(functionArgs)) {}

    string getPrototype();
    string getOverloadsFunctions();
    string getName();
    string getType();

private:
    string _functionName;
    string _functionType;
    vector<Functions> _overloadedFunctions;
    vector<string> _functionArgs;
};
#endif // FUNCTIONS_H
