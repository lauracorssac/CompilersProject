/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <unordered_map>
#include <string>
#include "SymbolTableValue.hpp"

#include "SyntacticalType.hpp"
extern "C" {
    
}

using namespace std;

class SymbolTable {
    private:
    unordered_map<string, SymbolTableValue> symbolTableLiterals;
    unordered_map<string, SymbolTableValue> symbolTableVariables;
    /* deslocamento em relacao ao rbss ou rfp */
    int offset;
    public:
    int getOffset();
    void incrementOffset(int increment);
    void insertNewItem(string key, SymbolTableValue value);
    bool hasKeyLiterals(string key);
    bool hasKeyVariables(string key);
    SymbolTableValue getValueForKey(string key);
    SymbolTable(int offset);
    unordered_map<string, SymbolTableValue> getTableVariables();
    unordered_map<string, SymbolTableValue> getTableLiterals();
    void updateType(string key, SyntacticalType type);
    void updateSizeString(string key, char *initializationString);
    void updateParameters(list<Parameter> parameters, string functionIdentifier);
};


#endif