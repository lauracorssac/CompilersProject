/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"
#include <unordered_map>
#include <list>
#include <iostream>
#include <utility>

SymbolTable::SymbolTable(OffsetAndScope scope) {
	this->scope = scope;
}

OffsetAndScope SymbolTable::getScopeAndOffset() {
	return this->scope;
}

void SymbolTable::incrementOffset(int increment){
	this->scope.offset += increment;
}

void SymbolTable::setOffset(int offset){
	this->scope.offset = offset;
}

void SymbolTable::insertNewItem(string key, SymbolTableValue value) {
	if (value.kind == literalKind) {
		if (this->hasKeyLiterals(key)) {
			freeLexicalValue(this->symbolTableLiterals[key].lexicalValue);
		}
        this->symbolTableLiterals[key] = value;
	} else {
		this->symbolTableVariables[key] = value;
	}
	
}
bool SymbolTable::hasKeyLiterals(string key) {
	return (this->symbolTableLiterals.find (key) != this->symbolTableLiterals.end());
}
bool SymbolTable::hasKeyVariables(string key) {
	return (this->symbolTableVariables.find (key) != this->symbolTableVariables.end());
}
SymbolTableValue SymbolTable::getValueForKey(string key) {
	return this->symbolTableVariables[key];
}
unordered_map<string, SymbolTableValue> SymbolTable::getTableVariables() {
	return this->symbolTableVariables;
}
unordered_map<string, SymbolTableValue> SymbolTable::getTableLiterals() {
	return this->symbolTableLiterals;
}
void SymbolTable::updateTypeAndOffset(string key, SyntacticalType type, int offset) {

	this->symbolTableVariables[key].type = type;
	this->symbolTableVariables[key].variableScope.offset = offset;

	if (this->symbolTableVariables[key].kind == vectorKind) {
		this->symbolTableVariables[key].size *= getSizeForSyntacticalType(type);
	} else {
		this->symbolTableVariables[key].size = getSizeForSyntacticalType(type);
	}
}
void SymbolTable::updateOffset(string key, int offset) {

	this->symbolTableVariables[key].variableScope.offset = offset;
}

void SymbolTable::updateSizeString(string key, char *initializationString) {
	this->symbolTableVariables[key].size = getSizeForStringType(initializationString);
}
void SymbolTable::updateParameters(list<Parameter> parameters, string functionIdentifier) {
	this->symbolTableVariables[functionIdentifier].listOfParameters = parameters;
	// como estamos trabalhando somente com inteiros, o tamanho total dos parâmetros é o número de item * 4
	this->symbolTableVariables[functionIdentifier].sizeOfParameters = parameters.size() * 4;
}

void SymbolTable::updateRegisters(pair<int, int> registersUsedFunction, string functionIdentifier) {
	this->symbolTableVariables[functionIdentifier].registersUsedFunction = registersUsedFunction;
}