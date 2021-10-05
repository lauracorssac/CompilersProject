
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

void SymbolTableStack::verifyIdentificatorNode(AST *identificatorNode) {
    LexicalValue *identificatorLV = identificatorNode->value;
    string variableKey = string(identificatorLV->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);
    if (resultVariable.found) {
        identificatorNode->sType = resultVariable.valueFound.type;
    } else {
        cout << "VARIABLE NOT FOUND" << endl;
    }
    
}

int SymbolTableStack::verifyInitializationVariable(LexicalValue *variableLV, int lineNumber) {

    string variableKey = string(variableLV->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);
    if (resultVariable.found) {
        ErrorManager::printDeclaredVariableInitialization(variableKey, resultVariable.valueFound, lineNumber);
        return ERR_DECLARED;
    }
    return SUCCESS;
}

void SymbolTableStack::makeInitialization(AST *variableNode, AST *initializationSymbolNode, AST *initializationValueNode, int lineNumber) {

    string variableKey = string(variableNode->value->literalTokenValueAndType.value.charSequenceValue);
    string attributionKey = this->stringFromLiteralValue(initializationValueNode->value->literalTokenValueAndType);
    
    //this case happens when trying to initialize with unexistent variable
    if (initializationValueNode->sType == undefinedSType) {
        return;
    }

    if (variableNode->sType == charSType && initializationValueNode->sType != charSType) {
        ErrorManager::printCharToXAttribution(variableKey, attributionKey, variableNode->sType, lineNumber);
        return;
    }
    if (variableNode->sType == stringSType && initializationValueNode->sType != stringSType) {
        ErrorManager::printStringToXAttribution(variableKey, attributionKey, variableNode->sType, lineNumber);
        return;
    }
    if (this->verifyCoersion(variableNode->sType, initializationValueNode->sType) != SUCCESS) {
        ErrorManager::printWrongTypeAttribution(variableKey, attributionKey, 
        variableNode->sType, 
        initializationValueNode->sType, lineNumber);
        return;
    }
  
    if (variableNode->sType == stringSType) {
        this->listOfTables.front().updateSizeString(variableKey, initializationValueNode->value->literalTokenValueAndType.value.charSequenceValue);
    }
    
    initializationSymbolNode->sType = variableNode->sType;

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
    // if (resultVariable.valueFound.kind == vectorKind) {
    //     ErrorManager::printVectorAttribution(variableKey, attributionKey, lineNumber);
    //     return ERR_VECTOR;
    // }
    if (resultAttribution.valueFound.type == charSType && resultVariable.valueFound.type != charSType) {
        ErrorManager::printCharToXAttribution(variableKey, attributionKey, resultVariable.valueFound.type, lineNumber);
        return ERR_CHAR_TO_X;
    }
    if (resultAttribution.valueFound.type == stringSType &&
     resultVariable.valueFound.type != stringSType) {
        ErrorManager::printStringToXAttribution(variableKey, attributionKey, resultVariable.valueFound.type, lineNumber);
        return ERR_STRING_TO_X;
    }
    if (this->verifyCoersion(resultVariable.valueFound.type, resultAttribution.valueFound.type) != SUCCESS) {
        ErrorManager::printWrongTypeAttribution(variableKey, attributionKey, 
        resultVariable.valueFound.type, 
        resultAttribution.valueFound.type, lineNumber);
        return ERR_WRONG_TYPE;
    }
    //ERR STRING MAX
    if (resultVariable.valueFound.type == stringSType && resultVariable.valueFound.size < resultAttribution.valueFound.size) {
        cout << "MAX STRING ERROR" << endl;
        return ERR_STRING_MAX;
    }
    return SUCCESS;
    
}

int SymbolTableStack::verifyCoersion(SyntacticalType variableType, SyntacticalType attributionType) {

    if (attributionType == variableType) { return SUCCESS; }

    if (attributionType == intSType && (variableType == floatSType || 
    variableType == boolSType)) {
        return SUCCESS;
    } 
    if (attributionType == floatSType && (variableType == intSType || 
    variableType == boolSType)) {
        return SUCCESS;
    }
    if (attributionType == boolSType && (variableType == floatSType || 
    variableType == intSType)) {
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

string SymbolTableStack::stringFromLiteralValue(LiteralTokenValueAndType literalTokenValueAndType) {
    
    LiteralTokenType litTokenType = literalTokenValueAndType.type;
    
    if (litTokenType == charSequenceType) {
        return string(literalTokenValueAndType.value.charSequenceValue);
    } else if (litTokenType == integerType) {
        return to_string(literalTokenValueAndType.value.integerValue);
    } else if (litTokenType == floatType) {
        return to_string(literalTokenValueAndType.value.floatValue);
    } else if (litTokenType == boolType) {
        return to_string(literalTokenValueAndType.value.boolValue);
    } else if (litTokenType == charType) {
        string convertedString(1, literalTokenValueAndType.value.charValue);
        return convertedString;
    } 
}

void SymbolTableStack::insertLiteral(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {
    
    string key = this->stringFromLiteralValue(lexicalValue->literalTokenValueAndType);
    cout << "inserting " << key << endl;
    SymbolTableValue newValue = createLiteral(line, column, lexicalValue, sType);
    this->insertNewItem(key, newValue);
}

void SymbolTableStack::insertVariableWithPendantType(int line, int column, LexicalValue *lexicalValue) {
    SymbolTableValue newValue = createVariableWithPendantType(line, column, lexicalValue);
    string key = string(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    this->variablesWithPendantTypes.push_back(key);
    this->insertNewItem(key, newValue);
}

void SymbolTableStack::insertVariableWithType(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {

    string key = string(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    if (this->find(key).found) { 
        cout << "Não foi possível declarar. Var já declarada" << endl;
        return; 
    }
    SymbolTableValue newValue = createVariableWithType(line, column, lexicalValue, sType);
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
    cout << "Printing total of " << this->listOfTables.size() << "tables" << endl;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        cout << "New Table:" << endl;
        for (auto kv: it->getTable()) {
            cout << endl;
            cout << "Key: " << kv.first << " Value: " << endl;
            printValue(kv.second);
        }
    }
}