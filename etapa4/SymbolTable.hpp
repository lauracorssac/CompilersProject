/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <unordered_map>
#include <string>
#include "SymbolTableValue.hpp"

using namespace std;

class SymbolTable {
    private:
    unordered_map<string, SymbolTableValue> symbolTable;
    public:
    void insertNewItem(string key, SymbolTableValue value);
    bool hasKey(string key);
    SymbolTableValue getValueForKey(string key);
    SymbolTable();
};


#endif