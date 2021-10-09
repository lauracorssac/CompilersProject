
#include "SymbolTableStack.hpp"
#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"
#include "ErrorManager.hpp"
#include <string>
#include <list>
#include <iostream>
#include "errors.h"
#include "Utils.hpp"

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

void SymbolTableStack::verifyVectorNode(AST *identificatorNode, AST *indexerSymbolNode, AST *indexerNode) {
    
    LexicalValue *identificatorLV = identificatorNode->value;
    string variableKey = string(identificatorLV->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);
    
    //Verifies ERR UNDECLARED
    if (!resultVariable.found) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorElementNotFound(variableKey);
        return;
    }
    // Verifies ERR VARIABLE
    if (resultVariable.valueFound.kind == variableKind) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorVariableVector(variableKey);
        return;
    }
    // Verifies ERR FUNCTION
    if (resultVariable.valueFound.kind == functionKind) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorFunctionVector(variableKey);
        return;
    }
    // Verifies ERR WRONG TYPE no indexador
    if (this->verifyCoersion(indexerNode->sType, intSType) != SUCCESS) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorWrongType(indexerNode, intSType);
        return;
    }

    identificatorNode->sType = resultVariable.valueFound.type;
    indexerSymbolNode->sType = resultVariable.valueFound.type;

}

void SymbolTableStack::verifyIdentificatorNode(AST *identificatorNode) {
    LexicalValue *identificatorLV = identificatorNode->value;
    string variableKey = string(identificatorLV->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);
    
    //Verifies ERR UNDECLARED
    if (!resultVariable.found) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorElementNotFound(variableKey);
    }
    // Verifies ERR VECTOR
    if (resultVariable.valueFound.kind == vectorKind) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorVectorVariable(variableKey);
    }
    // Verifies ERR FUNCTION
    if (resultVariable.valueFound.kind == functionKind) {
         ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorFunctionVariable(variableKey);
    }

    identificatorNode->sType = resultVariable.valueFound.type;
    
}

void SymbolTableStack::makeInitialization(AST *variableNode, AST *initializationSymbolNode, AST *initializationValueNode) {

    string variableKey = string(variableNode->value->literalTokenValueAndType.value.charSequenceValue);
    string attributionKey = stringFromLiteralValue(initializationValueNode->value->literalTokenValueAndType);

    //Verifies ERR CHAR TO X
    if (initializationValueNode->sType == charSType && variableNode->sType != charSType) {
        ErrorManager::printLine(initializationValueNode->value->lineNumber);
        ErrorManager::printAttributionError(variableKey, attributionKey);
        ErrorManager::errorCharToX(variableKey, initializationValueNode, variableNode->sType);
    }

    //Verifies ERR STRING TO X
    if (initializationValueNode->sType == stringSType && variableNode->sType != stringSType) {
        ErrorManager::printLine(initializationValueNode->value->lineNumber);
        ErrorManager::printAttributionError(variableKey, attributionKey);
        ErrorManager::errorStringToX(variableKey, attributionKey, variableNode->sType);
    }

    //Verifies ERR WRONG TYPE
    if (this->verifyCoersion(variableNode->sType, initializationValueNode->sType) != SUCCESS) {
        
        ErrorManager::printLine(initializationValueNode->value->lineNumber);
        ErrorManager::printAttributionError(variableKey, attributionKey);
        ErrorManager::errorWrongType(initializationValueNode, variableNode->sType);
        
    }
  
    if (variableNode->sType == stringSType) {
        this->listOfTables.front().updateSizeString(variableKey, initializationValueNode->value->literalTokenValueAndType.value.charSequenceValue);
    }
    
    initializationSymbolNode->sType = variableNode->sType;

}

void SymbolTableStack::makeAttributionVariable(AST *variableNode, AST *attributionSymbolNode, AST *attributionNode) {

    string variableKey = stringFromLiteralValue(variableNode->value->literalTokenValueAndType);
    
    //Verifies ERR_CHAR_TO_X
    if (attributionNode->sType == charSType && variableNode->sType != charSType) {
        ErrorManager::printLine(attributionSymbolNode->value->lineNumber);
        ErrorManager::errorCharToX(variableKey, attributionNode, variableNode->sType);
    }

    //Verifies ERR_STRING_TO_X
    if (attributionNode->sType == stringSType && variableNode->sType != stringSType) {
        ErrorManager::printLine(attributionSymbolNode->value->lineNumber);
        cout << "ERR_STRING_TO_X" << endl;
        return;
    }

    //ERR STRING MAX
    if (variableNode->sType == stringSType && attributionNode->sType == stringSType) {

        string attKey = stringFromLiteralValue(attributionNode->value->literalTokenValueAndType);
        SearchResult resultAttribution = this->find(attKey);
        SearchResult resultVariable = this->find(variableKey);
        if (!resultVariable.found || !resultAttribution.found) { cout << "aaa" << endl; return; }
        if (resultVariable.valueFound.size < resultAttribution.valueFound.size) {
            cout << "MAX STRING ERROR" << endl;
            return;
        }
    }

    //Verifies ERR_WRONG_TYPE
    if (this->verifyCoersion(variableNode->sType, attributionNode->sType) != SUCCESS) {
        
        ErrorManager::printLine(attributionSymbolNode->value->lineNumber);
        ErrorManager::errorWrongType(attributionNode, variableNode->sType);
        
    }

    attributionSymbolNode->sType = variableNode->sType;

}

void SymbolTableStack::makeAttributionVector(AST *identifierNode, AST *attributionSymbolNode, AST *attributionNode, 
    AST *indexerSymbolNode) {

    string variableKey = string(identifierNode->value->literalTokenValueAndType.value.charSequenceValue);

    //Verifies ERR_CHAR_TO_X
    if (attributionNode->sType == charSType && indexerSymbolNode->sType != charSType) {
        
        ErrorManager::printLine(attributionNode->value->lineNumber);
        ErrorManager::errorCharToX(variableKey, attributionNode, indexerSymbolNode->sType);
    }

    //Verifies ERR_STRING_TO_X
    if (attributionNode->sType == stringSType) {
        ErrorManager::printLine(attributionNode->value->lineNumber);
        string attKey = string(attributionNode->value->literalTokenValueAndType.value.charSequenceValue);
        ErrorManager::errorStringToX(variableKey, attKey, indexerSymbolNode->sType);
    }

    //Verifies ERR_WRONG_TYPE
    if (this->verifyCoersion(indexerSymbolNode->sType, attributionNode->sType) != SUCCESS) {
        ErrorManager::printLine(attributionNode->value->lineNumber);
        ErrorManager::errorWrongType(attributionNode, indexerSymbolNode->sType);
    }

    attributionSymbolNode->sType = indexerSymbolNode->sType;

}

void SymbolTableStack::makeInput(AST *inputNode, AST *identifierNode) {
    
    SyntacticalType type = identifierNode->sType;
    
    //Verifies ERR WRONG PAR INPUT
    if (type != intSType && type != floatSType) {
        ErrorManager::printLine(identifierNode->value->lineNumber);
        ErrorManager::errorInput(identifierNode);
    }

    inputNode->sType = type;

}

void SymbolTableStack::makeOutputIdentifier(AST *outputNode, AST *identifierNode) {
    
    SyntacticalType type = identifierNode->sType;
    
    //Verifies ERR WRONG PAR INPUT
    if (type != intSType && type != floatSType) {
        ErrorManager::printLine(identifierNode->value->lineNumber);
        ErrorManager::errorOutput(identifierNode);
    }

    outputNode->sType = type;

}

void SymbolTableStack::makeOutputLiteral(AST *outputNode, AST *literalNode) {
    
    SyntacticalType type = literalNode->sType;
    
    //Verifies ERR WRONG PAR INPUT
    if (type != intSType && type != floatSType) {
        ErrorManager::printLine(literalNode->value->lineNumber);
        ErrorManager::errorOutput(literalNode);
    }

    outputNode->sType = type;

}

void SymbolTableStack::makeShift(AST *shiftSumbolNode, AST *shiftLiteralNode) {
    
    int intValue = shiftLiteralNode->value->literalTokenValueAndType.value.integerValue;
    
    //Verifies ERR WRONG PAR SHIFT
    if (intValue > 16) {
        ErrorManager::printLine(shiftSumbolNode->value->lineNumber);
        ErrorManager::errorShift(shiftLiteralNode);
    }

    shiftSumbolNode->sType = intSType;
}

void SymbolTableStack::makeFunctionCall(AST *identificatorNode, AST *parametersNode) {

    string variableKey = string(identificatorNode->value->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);

    //Verifies ERR_UNDECLARED
    if (!resultVariable.found) {
        cout << "function not found" << endl;
        //ErrorManager::printElementNotFoundAttribution(variableKey, attributionKey, variableKey, lineNumber);
        return;
    }
    //Verifies ERR_VECTOR
    if (resultVariable.valueFound.kind == vectorKind) {
        cout << "err vector" << endl;
        //ErrorManager::printFunctionAttribution(variableKey, attributionKey, lineNumber);
        return;
    }
    //Verifies ERR_VARIABLE
    if (resultVariable.valueFound.kind == variableKind) {
        cout << "err variable" << endl;
        //ErrorManager::printVectorAttribution(variableKey, attributionKey, lineNumber);
        return;
    }

    list<Parameter>::iterator functionExpectedArg;
    functionExpectedArg = resultVariable.valueFound.listOfParameters.begin();
    AST *functionCallArg = parametersNode;

    // Verifies ERR MISSING ARGS
    if (parametersNode == NULL && resultVariable.valueFound.listOfParameters.size() != 0) {
        cout << "missing args" << endl;
        return;
    }
   
    while(functionCallArg != NULL && functionExpectedArg != resultVariable.valueFound.listOfParameters.end()) {

        // Verifies ERR WRONG TYPE ARGS
        if (verifyCoersion(functionCallArg->sType, functionExpectedArg->type) != SUCCESS) {
            cout << "ERR WRONG TYPE ARGS" << endl;
            return;
        }

        functionCallArg = functionCallArg->child;
        functionExpectedArg++;
    }
    // Verifies ERR MISSING ARGS
    if (functionCallArg == NULL && functionExpectedArg != resultVariable.valueFound.listOfParameters.end()) {
        cout << "missing args" << endl;
        return;
    }
    // Verifies ERR EXCESS AGRGS
    if (functionCallArg != NULL && functionExpectedArg == resultVariable.valueFound.listOfParameters.end()) {
        cout << "excess args" << endl;
        return;
    }

    identificatorNode->sType = resultVariable.valueFound.type;

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



void SymbolTableStack::insertLiteral(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {
    
    string key = stringFromLiteralValue(lexicalValue->literalTokenValueAndType);
    SymbolTableValue newValue = createLiteral(line, column, lexicalValue, sType);
    this->insertNewItem(key, newValue);
}

void SymbolTableStack::insertVariableWithPendantType(int line, int column, LexicalValue *lexicalValue) {
    
    SymbolTableValue newValue = createVariableWithPendantType(line, column, lexicalValue);
    string key = string(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    this->variablesWithPendantTypes.push_back(key);
    this->insertNewItem(key, newValue);
}

void SymbolTableStack::insertFunction(int line, int column, AST *identificatorNode, SyntacticalType sType) {
    
    string key = string(identificatorNode->value->literalTokenValueAndType.value.charSequenceValue);
    SearchResult searchResult = this->find(key);

    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }
    
    //Verifies ERR FUNCTION STRING
    if (sType == stringSType) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorFunctionString(identificatorNode);

    }

    SymbolTableValue newValue = createFunctionWithTypeNoParameters(line, column, identificatorNode->value, sType);
    this->insertNewItem(key, newValue);
    identificatorNode->sType = sType;
    this->lastDeclaredFunction = key;

}

void SymbolTableStack::makeReturn(AST *returnSymbolNode, AST *returnExpressionNode) {

    SymbolTableValue functionValue = this->listOfTables.back().getValueForKey(lastDeclaredFunction);

    //Verifies ERR WRONG PAR RETURN
    if (this->verifyCoersion(returnExpressionNode->sType, functionValue.type) != SUCCESS) {
        ErrorManager::printLine(returnExpressionNode->value->lineNumber);
        ErrorManager::errorReturn(returnExpressionNode, lastDeclaredFunction, 
        functionValue.type, functionValue.line);
    }

    returnSymbolNode->sType = functionValue.type;

}

void SymbolTableStack::updateFunctionWithPendantParameters() {

    this->listOfTables.back().updateParameters(this->pendantParameters, this->lastDeclaredFunction);
    this->pendantParameters.clear();
}

void SymbolTableStack::insertParameterWithType(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {

    string key = string(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    if (this->find(key).found) { 
        cout << "Não foi possível declarar. Var já declarada" << endl;
        return; 
    }

    //Verifies ERR FUNCTION STRING
    if (sType == stringSType) {
        cout << "ERR FUNCTION STRING" << endl;
        return; //nao insere dai?
    }

    SymbolTableValue newValue = createVariableWithType(line, column, lexicalValue, sType);
    this->insertNewItem(key, newValue);
    Parameter newParam = {.type = sType};
    this->pendantParameters.push_back(newParam);
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

        //VECTOR OF STRING ERROR
        if (this->listOfTables.front().getValueForKey(varKey).kind == vectorKind && type == stringSType) {
            cout << "VECTOR OF STRING ERROR" << endl;
            this->variablesWithPendantTypes.pop_front();
            continue;
        }
        this->listOfTables.front().updateType(varKey, type);
        this->variablesWithPendantTypes.pop_front();
    }

}

SyntacticalType SymbolTableStack::getInferenceBinaryOperation(SyntacticalType type1, SyntacticalType type2) {

    if (type1 == undefinedSType || type2 == undefinedSType) { return undefinedSType; } 

    //Verifies STRING CHAR TO X
    if (type1 == stringSType || type2 == stringSType) { 
        cout << "ERR STRING TO X" << endl;
        return undefinedSType; 
    }

    //Verifies ERR CHAR TO X
    if (type1 == charSType || type2 == charSType) { 
        cout << "ERR CHAR TO X" << endl;
        return undefinedSType; 
    }

    if (type1 == type2) { return type1; }
    if (type1 == floatSType || type2 == floatSType) { return floatSType; }
    return intSType;

}

void SymbolTableStack::makeTernaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node, AST *exp3Node) {

    SyntacticalType type1 = exp1Node->sType;
    SyntacticalType type2 = exp2Node->sType;
    SyntacticalType type3 = exp3Node->sType;

    SyntacticalType partialType = this->getInferenceBinaryOperation(type1, type2);
    SyntacticalType finalType = this->getInferenceBinaryOperation(partialType, type3);

    if(finalType == undefinedSType) { return; }

    operandNode->sType = finalType; 
}

void SymbolTableStack::makeBinaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node) {

    SyntacticalType type1 = exp1Node->sType;
    SyntacticalType type2 = exp2Node->sType;
    SyntacticalType finalType = this->getInferenceBinaryOperation(type1, type2);

    if(this->getInferenceBinaryOperation(type1, type2) == undefinedSType) {
        return;
    }

    operandNode->sType = finalType; 
}

void SymbolTableStack::makeUnaryOperation(AST *exp1Node, AST *operandNode) {

    SyntacticalType type1 = exp1Node->sType;
    
    //Verifies ERR CHAR TO X
    if (type1 == charSType) {
        cout << "ERR CHAR TO X" << endl;
        return;
    } 

    //Verifies ERR STRING TO X
    if (type1 == stringSType) {
        cout << "ERR STRING TO X" << endl;
        return;
    }

    operandNode->sType = type1;
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