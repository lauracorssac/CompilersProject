/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"

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