#ifndef PARSER_H
#define PARSER_H
#include <INCLUDES.h>

class Parser
{
public:
    Parser(){};
    Parser(string &&str);
    pair<int,int> searchInfiniteLoops();
    vector<Variable> getVariables();
    vector<Functions> getFunctions();
    vector<int> getComplexStructs();
    vector<pair<int,int>> getChangePosition();
    vector<pair<int,int>> getBranches();




private:
    void _searchVariables();
    void _searchFunctions();
    string _str;
    vector<Variable> _variables;
    vector<Functions> _functions;


};
#endif // PARSER_H
