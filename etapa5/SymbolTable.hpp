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
    OffsetAndScope scope;
    public:
    OffsetAndScope getScopeAndOffset();
    void incrementOffset(int increment);
    void insertNewItem(string key, SymbolTableValue value);
    bool hasKeyLiterals(string key);
    bool hasKeyVariables(string key);
    SymbolTableValue getValueForKey(string key);
    SymbolTable(OffsetAndScope scope);
    unordered_map<string, SymbolTableValue> getTableVariables();
    unordered_map<string, SymbolTableValue> getTableLiterals();
    void updateTypeAndOffset(string key, SyntacticalType type, int offset);
    void updateSizeString(string key, char *initializationString);
    void updateParameters(list<Parameter> parameters, string functionIdentifier);
};


#endif