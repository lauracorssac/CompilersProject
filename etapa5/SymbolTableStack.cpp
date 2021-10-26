/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTableStack.hpp"
#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"
#include "CodeGenerator.hpp"
#include "ErrorManager.hpp"
#include <string>
#include <list>
#include <iostream>
#include <cstring>
#include <unordered_map>
#include "errors.h"
#include "Utils.hpp"
#include "Code.hpp"

using namespace std;

extern CodeGenerator codeGenerator;
#include "SyntacticalType.hpp"
extern "C" {
    
}

SymbolTableStack::SymbolTableStack() {
    this->mainWasDeclared = false;
}

OffsetAndScope SymbolTableStack::getOffsetAndScopeNewScope() {
    int size = this->listOfTables.size();

    // caso esteja começando o escopo global
    if ( size == 0) { return { .scope=global, .offset=0}; }

    // caso esteja começando uma funcao
    if ( size == 1) { return {.scope=local, .offset=0}; }

    // caso esteja começando um escopo alinhado
    return this->listOfTables.front().getScopeAndOffset();
}

void SymbolTableStack::beginNewScope() {

    SymbolTable newSymbolTable = SymbolTable(this->getOffsetAndScopeNewScope());
    this->listOfTables.push_front(newSymbolTable);
    
}
SearchResult SymbolTableStack::find(string element) {

    list<SymbolTable>::iterator it;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        if(it->hasKeyVariables(element)) {
            
            SearchResult returnValue = { .found= true, .valueFound= it->getValueForKey(element) };
            return returnValue;
        }
    }
    
    SymbolTableValue emptySymbolTableValue;
    SearchResult returnValue = { .found= false, .valueFound= emptySymbolTableValue };
    return returnValue;
}

SearchResult SymbolTableStack::findInScope(string element) {

    if (this->listOfTables.empty()) { return {.found= false }; }
    SymbolTable currentScopeTable = this->listOfTables.front();
    if(currentScopeTable.hasKeyVariables(element)) {
            
        SearchResult returnValue = { .found= true, .valueFound= currentScopeTable.getValueForKey(element) };
        return returnValue;
    }
    return { .found= false };
}

void SymbolTableStack::endLastScope() {

    if (this->listOfTables.empty()) { return; }
    SymbolTable lastScope = this->listOfTables.front();
    int lastOffset = lastScope.getScopeAndOffset().offset;

    /* frees identifiers's table */
    for (pair<string, SymbolTableValue> kv : lastScope.getTableVariables()) {
        
        freeLexicalValue(kv.second.lexicalValue);
    }
    /* frees literals's table */
    for (pair<string, SymbolTableValue> kv : lastScope.getTableLiterals()) {
        
        freeLexicalValue(kv.second.lexicalValue);
    }
    this->listOfTables.pop_front();
    
    int size = this->listOfTables.size();
    if (size > 1) {
        this->listOfTables.front().setOffset(lastOffset);
    } else {
        this->listOfTables.front().updateOffset(lastDeclaredFunction, lastOffset);
        this->lastFunctionOffset = lastOffset;
    }

}

int SymbolTableStack::getLastFunctionOffset() {
    return this->lastFunctionOffset;
}

int SymbolTableStack::geSizeOfParametersLastDeclaredFunction() {

    return this->getSizeOfParametersForFunction(this->lastDeclaredFunction);
}

OffsetAndScope SymbolTableStack::getUpdatedOffsetAndScopeForVariable(AST *variableNode) {

    string variableName = stringFromLiteralValue(variableNode->value->literalTokenValueAndType);
    SearchResult searchResult = this->find(variableName);
    if (!searchResult.found) {
        ErrorManager::errorElementNotFound(variableName);
    }

    if (searchResult.valueFound.variableScope.scope == global) {
        return searchResult.valueFound.variableScope;
    } else {
        int variableDeclarationOffset = searchResult.valueFound.variableScope.offset;
        int sizeOfParameters = this->geSizeOfParametersLastDeclaredFunction();
        return {.scope=local, .offset= sizeOfParameters + variableDeclarationOffset + 16};
    }

}

int SymbolTableStack::getReturnValueOffsetForLastDeclaredFunction() {

    return getReturnValueOffsetForFunction(lastDeclaredFunction);
   
}

int SymbolTableStack::getReturnValueOffsetForFunction(string functionName) {

    return this->getSizeOfParametersForFunction(functionName) + 12;

}

void SymbolTableStack::endAllScopes() {

    if (this->listOfTables.empty()) { return; }
    list<SymbolTable>::iterator it;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        /* frees identifiers's table */
       for (pair<string, SymbolTableValue> kv : it->getTableVariables()) {
            freeLexicalValue(kv.second.lexicalValue);
        }
        /* frees literals's table */
        for (pair<string, SymbolTableValue> kv : it->getTableLiterals()) {
            freeLexicalValue(kv.second.lexicalValue);
        }
    }
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
    string attKey = stringFromLiteralValue(attributionNode->value->literalTokenValueAndType);
    
    //Verifies ERR_CHAR_TO_X
    if (attributionNode->sType == charSType && variableNode->sType != charSType) {
        ErrorManager::printLine(attributionSymbolNode->value->lineNumber);
        ErrorManager::errorCharToX(variableKey, attributionNode, variableNode->sType);
    }

    //Verifies ERR_STRING_TO_X
    if (attributionNode->sType == stringSType && variableNode->sType != stringSType) {
        ErrorManager::printLine(attributionSymbolNode->value->lineNumber);
        ErrorManager::errorStringToX(variableKey, attKey, variableNode->sType);
    }

    //ERR STRING MAX
    if (variableNode->sType == stringSType && attributionNode->sType == stringSType) {


        string attKey = stringFromLiteralValue(attributionNode->value->literalTokenValueAndType);
        SearchResult resultAttribution = this->find(attKey);
        SearchResult resultVariable = this->find(variableKey);
        if (!resultVariable.found || !resultAttribution.found) { ErrorManager::errorException(); }

        if (resultVariable.valueFound.size < resultAttribution.valueFound.size) {
            
            ErrorManager::printLine(attributionNode->value->lineNumber);
            ErrorManager::errorMaxString(variableNode, attributionNode, resultVariable.valueFound.size);

        }
    }

    //Verifies ERR_WRONG_TYPE
    if (this->verifyCoersion(variableNode->sType, attributionNode->sType) != SUCCESS) {
        
        ErrorManager::printLine(attributionSymbolNode->value->lineNumber);
        ErrorManager::errorWrongType(attributionNode, variableNode->sType);
        
    }


    attributionSymbolNode->sType = variableNode->sType;

}

void SymbolTableStack::makeAttributionVector(AST *attributionSymbolNode, AST *attributionNode, 
    AST *indexerSymbolNode) {

    string variableKey = stringFromLiteralValue(indexerSymbolNode->child->value->literalTokenValueAndType);

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
    
    int intValueLeft = shiftLiteralNode->value->literalTokenValueAndType.value.integerValue;
    
    //Verifies ERR WRONG PAR SHIFT
    if (intValueLeft > 16) {
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
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorElementNotFound(variableKey);
    }
    //Verifies ERR_VECTOR
    if (resultVariable.valueFound.kind == vectorKind) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorVectorFunction(variableKey);
    }
    //Verifies ERR_VARIABLE
    if (resultVariable.valueFound.kind == variableKind) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorVariableFunction(variableKey);
    }

    list<Parameter>::iterator functionExpectedArg;
    functionExpectedArg = resultVariable.valueFound.listOfParameters.begin();
    AST *functionCallArg = parametersNode;
    int expectedParametersNumber = resultVariable.valueFound.listOfParameters.size();
    int givenParametersNumber = this->countNumberOfGivenParameters(functionCallArg);

    //Verifies ERR MISSING ARGS and ERR EXCESS ARGS
    if (givenParametersNumber != expectedParametersNumber) {
        ErrorManager::printLine(identificatorNode->value->lineNumber);
        ErrorManager::errorWrongQuantityParameters(identificatorNode, expectedParametersNumber, givenParametersNumber);
    }
   
    int position = 0;
    while(functionCallArg != NULL && functionExpectedArg != resultVariable.valueFound.listOfParameters.end()) {

        // Verifies ERR WRONG TYPE ARGS
        if (verifyCoersion(functionCallArg->sType, functionExpectedArg->type) != SUCCESS) {
           ErrorManager::printLine(identificatorNode->value->lineNumber);
           ErrorManager::errorWrongTypeParameters(identificatorNode, functionExpectedArg->type, position, functionCallArg);
        }

        functionCallArg = functionCallArg->child;
        functionExpectedArg++;
        position += 1;
    }

    identificatorNode->sType = resultVariable.valueFound.type;
    
}

int SymbolTableStack::countNumberOfGivenParameters(AST *functionCallNode) {

    return functionCallNode->numberOfParameters;
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

    string key = stringFromLiteralValue(lexicalValue->literalTokenValueAndType);
    SearchResult searchResult = this->findInScope(key);

    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(line);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }

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

    string key = stringFromLiteralValue(lexicalValue->literalTokenValueAndType);
    SearchResult searchResult = this->findInScope(key);

    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(line);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }
    
    OffsetAndScope scope = this->listOfTables.front().getScopeAndOffset();
    SymbolTableValue newValue = createVariableWithPendantType(line, column, lexicalValue, scope);
    this->variablesWithPendantTypes.push_back(key);
    this->insertNewItem(key, newValue);
}

int SymbolTableStack::generateLabelForFunction(string functionName) {

    if (strcmp(functionName.c_str(), "main") == 0) {
        if (this->mainWasDeclared) { ErrorManager::doubleDeclarationOfMain(); }
        this->mainWasDeclared = true;
        return 0;
    } else {
        return codeGenerator.getLabel();
    }

}

int SymbolTableStack::getLabelForFunction(AST *functionNode) {
    
    string functionName = stringFromLiteralValue(functionNode->value->literalTokenValueAndType);
    int hasKey = this->listOfTables.back().hasKeyVariables(functionName);
    if (!hasKey) { ErrorManager::errorException(); }
    
    return this->listOfTables.back().getValueForKey(functionName).functionLabel;

}
int SymbolTableStack::getQuantityOfParametersForFunction(string functionName) {
   
    int hasKey = this->listOfTables.back().hasKeyVariables(functionName);
    if (!hasKey) { ErrorManager::errorException(); }
    return this->listOfTables.back().getValueForKey(functionName).listOfParameters.size();
}

int SymbolTableStack::getQuantityOfParametersForFunction(AST *functionNode) {

    string functionName = stringFromLiteralValue(functionNode->value->literalTokenValueAndType);
    return getQuantityOfParametersForFunction(functionName);
}

int SymbolTableStack::getSizeOfParametersForFunction(string functionName) {
   
    int hasKey = this->listOfTables.back().hasKeyVariables(functionName);
    if (!hasKey) { ErrorManager::errorException(); }
    return this->listOfTables.back().getValueForKey(functionName).sizeOfParameters;
}

int SymbolTableStack::getSizeOfParametersForFunction(AST *functionNode) {

    string functionName = stringFromLiteralValue(functionNode->value->literalTokenValueAndType);
    return getSizeOfParametersForFunction(functionName);
}

void SymbolTableStack::insertFunction(int line, int column, AST *identificatorNode, SyntacticalType sType) {
    
    string key = string(identificatorNode->value->literalTokenValueAndType.value.charSequenceValue);
    SearchResult searchResult = this->findInScope(key);

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

    int functionLabel = generateLabelForFunction(key);
    SymbolTableValue newValue = createFunctionWithTypeNoParameters(line, column, identificatorNode->value, sType, functionLabel);
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

    string key = stringFromLiteralValue(lexicalValue->literalTokenValueAndType);
    SearchResult searchResult = this->findInScope(key);
    
    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(line);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }

    //Verifies ERR FUNCTION STRING
    if (sType == stringSType) {
        ErrorManager::printLine(line);
        ErrorManager::errorFunctionStringParameter(key);
    }

    SymbolTable currentScope = this->listOfTables.front();
    int offsetFunction = currentScope.getScopeAndOffset().offset;
    OffsetAndScope offsetAndScopeVariable = {.scope=local, .offset=offsetFunction};
    
    SymbolTableValue newValue = createVariableWithType(line, column, lexicalValue, sType, offsetAndScopeVariable);
    this->listOfTables.front().incrementOffset(newValue.size);
    this->insertNewItem(key, newValue);
    Parameter newParam = {.type = sType};
    this->pendantParameters.push_back(newParam);
}

void SymbolTableStack::insertVariableWithType(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {

    string key = string(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    SearchResult searchResult = this->findInScope(key);

    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(line);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }

    OffsetAndScope offsetAndScope = this->listOfTables.front().getScopeAndOffset();
    SymbolTableValue newValue = createVariableWithType(line, column, lexicalValue, sType, offsetAndScope);
    this->listOfTables.front().incrementOffset(newValue.size);
    this->insertNewItem(key, newValue);
}

void SymbolTableStack::updateTypeOfVariablesWithPendantTypes(SyntacticalType type) {

    while (!this->variablesWithPendantTypes.empty()) {
        string varKey = this->variablesWithPendantTypes.front();

        //Verifies ERR VEC STRING
        SymbolTableValue value = this->listOfTables.front().getValueForKey(varKey);
        if (value.kind == vectorKind && type == stringSType) {
            
            ErrorManager::printLine(value.line);
            ErrorManager::errorStringVector(varKey);
        }

        this->listOfTables.front().updateTypeAndOffset(
            varKey, type, 
            this->listOfTables.front().getScopeAndOffset().offset
        );
        SymbolTableValue updatedValue = this->listOfTables.front().getValueForKey(varKey);
        this->listOfTables.front().incrementOffset(updatedValue.size);
        this->variablesWithPendantTypes.pop_front();
    }

}

SyntacticalType SymbolTableStack::getInferenceBinaryOperation(SyntacticalType type1, SyntacticalType type2) {

    if (type1 == undefinedSType || type2 == undefinedSType 
    || type1 == stringSType || type2 == stringSType ||
    type1 == charSType || type2 == charSType) { return undefinedSType; } 

    if (type1 == type2) { return type1; }
    if (type1 == floatSType || type2 == floatSType) { return floatSType; }
    return intSType;

}

void SymbolTableStack::checkStringCharOperation(AST *exp1Node) {

    SyntacticalType type1 = exp1Node->sType;

    //Verifies ERR_STRING_TO_X and CHAR TO X
    if (type1 == stringSType || type1 == charSType) { 
        ErrorManager::printLine(exp1Node->value->lineNumber);
        ErrorManager::errorCharOrStringToXOperation(exp1Node, type1);
    }
}

void SymbolTableStack::makeTernaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node, AST *exp3Node) {

    SyntacticalType type1 = exp1Node->sType;
    SyntacticalType type2 = exp2Node->sType;
    SyntacticalType type3 = exp3Node->sType;

    this->checkStringCharOperation(exp1Node);
    this->checkStringCharOperation(exp2Node);
    this->checkStringCharOperation(exp3Node);

    SyntacticalType partialType = this->getInferenceBinaryOperation(type1, type2);
    SyntacticalType finalType = this->getInferenceBinaryOperation(partialType, type3);

    if(finalType == undefinedSType) { ErrorManager::errorException(); }

    operandNode->sType = finalType; 
}

void SymbolTableStack::makeBinaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node) {

    SyntacticalType type1 = exp1Node->sType;
    SyntacticalType type2 = exp2Node->sType;
    SyntacticalType finalType = this->getInferenceBinaryOperation(type1, type2);

    this->checkStringCharOperation(exp1Node);
    this->checkStringCharOperation(exp2Node);

    if(this->getInferenceBinaryOperation(type1, type2) == undefinedSType) {
        ErrorManager::errorException();
    }

    operandNode->sType = finalType; 
}

void SymbolTableStack::makeUnaryOperation(AST *exp1Node, AST *operatorSymbolNode) {

    SyntacticalType type1 = exp1Node->sType;
    string key = stringFromLiteralValue(exp1Node->value->literalTokenValueAndType);
    
    this->checkStringCharOperation(exp1Node);

    operatorSymbolNode->sType = type1;
}

void SymbolTableStack::printItself() {

    list<SymbolTable>::iterator it;
    cout << "Printing total of " << this->listOfTables.size() << "tables" << endl;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        cout << "New Table:" << endl;
        for (auto kv : it->getTableVariables()) {
            cout << endl;
            cout << "Key: " << kv.first << " Value: " << endl;
            printValue(kv.second);
        }
        for (auto kv : it->getTableLiterals()) {
            cout << endl;
            cout << "Key: " << kv.first << " Value: " << endl;
            printValue(kv.second);
        }
    }
}