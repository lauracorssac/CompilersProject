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
    /* o deslocamento aqui é como o "indice" da variavel local */
    /* a primeira declaracao, podendo ser parametro ou nao, possui offset = 0 */
    OffsetAndScope scope;
    
    public:
    OffsetAndScope getScopeAndOffset();
    void updateOffset(string key, int offset);
    void incrementOffset(int increment);
    void setOffset(int offset); 
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
    void updateRegisters(pair<int, int> registersUsedFunction, string functionIdentifier);
};


#endif