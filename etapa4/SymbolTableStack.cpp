
#include "SymbolTableStack.hpp"
#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"
#include "ErrorManager.hpp"
#include <string>
#include <list>
#include <iostream>
#include "errors.h"

using namespace std;

extern "C" {
    #include "SyntacticalType.h"
}

SymbolTableStack::SymbolTableStack() {
    // começa o escopo global
    this->beginNewScope(); 
}

void SymbolTableStack::beginNewScope() {

    SymbolTable newSymbolTable;
    this->listOfTables.push_front(newSymbolTable);
    
}
SearchResult SymbolTableStack::find(string element) {

    list<SymbolTable>::iterator it;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        if(it->hasKey(element)) {
            
            SearchResult returnValue = { .found= true, .valueFound= it->getValueForKey(element) };
            return returnValue;
        }
    }
    
    SymbolTableValue emptySymbolTableValue;
    SearchResult returnValue = { .found= false, .valueFound= emptySymbolTableValue };
    return returnValue;
}

void SymbolTableStack::endLastScope() {
    this->listOfTables.pop_front();
}
void SymbolTableStack::insertNewItem(string key, SymbolTableValue value) {
    
    this->listOfTables.front().insertNewItem(key, value);
}

int SymbolTableStack::verifyAttribution(string variableKey, string attributionKey, int lineNumber) {

    SearchResult resultVariable = this->find(variableKey);
    SearchResult resultAttribution = this->find(attributionKey);

    if (!resultVariable.found && !resultAttribution.found) {
        ErrorManager::printElementsNotFoundAttribution(variableKey, attributionKey, lineNumber);
        return ERR_UNDECLARED;
    }
    if (!resultVariable.found) {
        ErrorManager::printElementNotFoundAttribution(variableKey, attributionKey, variableKey, lineNumber);
        return ERR_UNDECLARED;
    }
    if (!resultAttribution.found) {
        ErrorManager::printElementNotFoundAttribution(variableKey, attributionKey, attributionKey, lineNumber);
        return ERR_UNDECLARED;
    }
    if (resultVariable.valueFound.kind == functionKind) {
        ErrorManager::printFunctionAttribution(variableKey, attributionKey, lineNumber);
        return ERR_FUNCTION;
    }
    if (resultAttribution.valueFound.type == charSType && resultVariable.valueFound.type != charSType) {
        ErrorManager::printCharToXAttribution(variableKey, attributionKey, resultVariable.valueFound.type, lineNumber);
        return ERR_CHAR_TO_X;
    }
    if (resultAttribution.valueFound.type == stringSType &&
     resultVariable.valueFound.type != stringSType) {
        ErrorManager::printStringToXAttribution(variableKey, attributionKey, resultVariable.valueFound.type, lineNumber);
        return ERR_STRING_TO_X;
    }
    if (this->verifyCoersion(resultVariable.valueFound.type, resultAttribution.valueFound.type) == SUCCESS) {
        return SUCCESS;
    } else {
        ErrorManager::printWrongTypeAttribution(variableKey, attributionKey, 
        resultVariable.valueFound.type, 
        resultAttribution.valueFound.type, lineNumber);
        return ERR_WRONG_TYPE;
    }
    
}

int SymbolTableStack::verifyCoersion(SyntacticalType variableType, SyntacticalType attributionType) {

    if (attributionType == intSType && (variableType == intSType || 
    variableType == floatSType || 
    variableType == boolSType)) {
        return SUCCESS;
    } 
    if (attributionType == floatSType && (variableType == floatSType || 
    variableType == intSType || 
    variableType == boolSType)) {
        return SUCCESS;
    }
    if (attributionType == boolSType && (variableType == floatSType || 
    variableType == intSType || 
    variableType == boolSType)) {
        return SUCCESS;
    }
    return GENERIC_ERROR;

}

void SymbolTableStack::insertVectorWithPendantType(int line, int column, 
LexicalValue *lexicalValue, int indexerValue) {

    string key = string(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    // if (lastDeclaredType == stringSType) {
    //     return ErrorManager::printStringVector(key);
    // }
    this->variablesWithPendantTypes.push_back(key);
    SymbolTableValue newValue = createVectorWithPendantType(line, column, lexicalValue, indexerValue);
    this->insertNewItem(key, newValue);

}

void SymbolTableStack::insertVariableWithPendantType(int line, int column, LexicalValue *lexicalValue) {
    SymbolTableValue newValue = createVariableWithPendantType(line, column, lexicalValue);
    string key = string(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    this->variablesWithPendantTypes.push_back(key);
    this->insertNewItem(key, newValue);
}

void SymbolTableStack::updateTypeOfVariablesWithPendantTypes(SyntacticalType type) {
    
    while (!this->variablesWithPendantTypes.empty()) {
        string varKey = this->variablesWithPendantTypes.front();
        this->listOfTables.front().updateType(varKey, type);
        this->variablesWithPendantTypes.pop_front();
    }

}

void SymbolTableStack::printItself() {

    list<SymbolTable>::iterator it;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        cout << endl;
        cout << "New Table:" << endl;
        for (auto kv: it->getTable()) {
            cout << endl;
            cout << "Key: " << kv.first << " Value: " << endl;
            printValue(kv.second);
        }
    }
}