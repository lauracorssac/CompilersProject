/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"
#include <unordered_map>

SymbolTable::SymbolTable() {}

void SymbolTable::insertNewItem(string key, SymbolTableValue value) {
	this->symbolTable[key] = value;
}
bool SymbolTable::hasKey(string key) {
	return (this->symbolTable.find (key) != this->symbolTable.end());
}
SymbolTableValue SymbolTable::getValueForKey(string key) {
	return this->symbolTable[key];
}
unordered_map<string, SymbolTableValue> getTable() {
	return this->symbolTable;
}