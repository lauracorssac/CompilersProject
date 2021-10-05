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
unordered_map<string, SymbolTableValue> SymbolTable::getTable() {
	return this->symbolTable;
}
void SymbolTable::updateType(string key, SyntacticalType type) {
	this->symbolTable[key].type = type;
	if (this->symbolTable[key].kind == vectorKind) {
		this->symbolTable[key].size *= getSizeForSyntacticalType(type);
	} else {
		this->symbolTable[key].size = getSizeForSyntacticalType(type);
	}
}