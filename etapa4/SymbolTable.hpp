/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <unordered_map>
#include <string>
#include "SymbolTableValue.hpp"

extern "C" {
    #include "SyntacticalType.h"
}

using namespace std;

class SymbolTable {
    private:
    unordered_map<string, SymbolTableValue> symbolTableLiterals;
    unordered_map<string, SymbolTableValue> symbolTableVariables;
    public:
    void insertNewItem(string key, SymbolTableValue value);
    bool hasKeyLiterals(string key);
    bool hasKeyVariables(string key);
    SymbolTableValue getValueForKey(string key);
    SymbolTable();
    unordered_map<string, SymbolTableValue> getTableVariables();
    unordered_map<string, SymbolTableValue> getTableLiterals();
    void updateType(string key, SyntacticalType type);
    void updateSizeString(string key, char *initializationString);
    void updateParameters(list<Parameter> parameters, string functionIdentifier);
};


#endif