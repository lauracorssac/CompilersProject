
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

void SymbolTableStack::verifyVectorNode(AST *identificatorNode, AST *indexerSymbolNode, AST *indexerNode) {
    LexicalValue *identificatorLV = identificatorNode->value;
    string variableKey = string(identificatorLV->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);
    
    //Verifies ERR UNDECLARED
    if (!resultVariable.found) {
        cout << "VARIABLE NOT FOUND" << endl;
        return;
    }
    // Verifies ERR VARIABLE
    if (resultVariable.valueFound.kind == variableKind) {
        cout << "ERR VARIABLE" << endl;
        return;
    }
    // Verifies ERR FUNCTION
    if (resultVariable.valueFound.kind == functionKind) {
        cout << "ERR FUNCTION" << endl;
        return;
    }
    // Verifies ERR WRONG TYPE no indexador
    if (indexerNode->sType != intSType) {
        cout << "ERR WRONG TYPE" << endl;
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
        cout << "VARIABLE NOT FOUND" << endl;
        return;
    }
    // Verifies ERR VECTOR
    if (resultVariable.valueFound.kind == vectorKind) {
        cout << "ERR VECTOR" << endl;
        return;
    }
    // Verifies ERR FUNCTION
    if (resultVariable.valueFound.kind == functionKind) {
        cout << "ERR FUNCTION" << endl;
        return;
    }

    identificatorNode->sType = resultVariable.valueFound.type;
    
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

void SymbolTableStack::makeAttributionVariable(AST *variableNode, AST *attributionSymbolNode, AST *attributionNode, int lineNumber) {

    string variableKey = string(variableNode->value->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);

    //this case happens when trying to initialize with unexistent variable
    if (attributionNode->sType == undefinedSType) {
        return;
    }
    //Verifies ERR_UNDECLARED
    if (!resultVariable.found) {
        cout << "printElementNotFoundAttribution" << endl;
        //ErrorManager::printElementNotFoundAttribution(variableKey, attributionKey, variableKey, lineNumber);
        return;
    }
    //Verifies ERR_FUNCTION
    if (resultVariable.valueFound.kind == functionKind) {
        cout << "printFunctionAttribution" << endl;
        //ErrorManager::printFunctionAttribution(variableKey, attributionKey, lineNumber);
        return;
    }
    //Verifies ERR_VECTOR
    if (resultVariable.valueFound.kind == vectorKind) {
        cout << "printVectorAttribution" << endl;
        //ErrorManager::printVectorAttribution(variableKey, attributionKey, lineNumber);
        return;
    }
    //Verifies ERR_CHAR_TO_X
    if (attributionNode->sType == charSType && resultVariable.valueFound.type != charSType) {
        cout << "printCharToXAttribution" << endl;
        //ErrorManager::printCharToXAttribution(variableKey, attributionKey, resultVariable.valueFound.type, lineNumber);
        return;
    }
    //Verifies ERR_STRING_TO_X
    if (attributionNode->sType == stringSType && resultVariable.valueFound.type != stringSType) {
        cout << "printStringToXAttribution" << endl;
        //ErrorManager::printStringToXAttribution(variableKey, attributionKey,  resultVariable.valueFound.type, lineNumber);
        return;
    }

    //Verifies ERR_WRONG_TYPE
    if (this->verifyCoersion(resultVariable.valueFound.type, attributionNode->sType) != SUCCESS) {
        
        cout << "printWrongTypeAttribution" << endl;
        //ErrorManager::printWrongTypeAttribution(variableKey, attributionKey, 
        //resultVariable.valueFound.type, 
        //resultAttribution.valueFound.type, lineNumber);
        return;
    }

    //ERR STRING MAX
    if (resultVariable.valueFound.type == stringSType) {
        string attKey = string(attributionNode->value->literalTokenValueAndType.value.charSequenceValue);
        SearchResult resultAttribution = this->find(attKey);
        if (!resultVariable.found) { cout << "Algo de errado nao esta certo"<< endl; return; }
        if (resultVariable.valueFound.size < resultAttribution.valueFound.size) {
            cout << "MAX STRING ERROR" << endl;
            return;
        }
    }

    variableNode->sType = resultVariable.valueFound.type;
    attributionSymbolNode->sType = resultVariable.valueFound.type;

}

void SymbolTableStack::makeAttributionVector(AST *variableNode, AST *attributionSymbolNode, AST *attributionNode, 
    AST *indexerSymbolNode, AST *indexerNode, int lineNumber) {

    string variableKey = string(variableNode->value->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);

    //Verifies if indexerExp is int. If not, prints ERR_WRONG_TYPE
    if (indexerNode->sType != intSType) {
        cout << "indexer must be int" << endl;
        return;
    }

    //this case happens when trying to initialize with unexistent variable or bad expression
    if (attributionNode->sType == undefinedSType) {
        return;
    }
    //Verifies ERR_UNDECLARED
    if (!resultVariable.found) {
        cout << "printElementNotFoundAttribution" << endl;
        //ErrorManager::printElementNotFoundAttribution(variableKey, attributionKey, variableKey, lineNumber);
        return;
    }
    //Verifies ERR_FUNCTION
    if (resultVariable.valueFound.kind == functionKind) {
        cout << "printFunctionAttribution" << endl;
        //ErrorManager::printFunctionAttribution(variableKey, attributionKey, lineNumber);
        return;
    }
    //Verifies ERR_VARIABLE
    if (resultVariable.valueFound.kind == variableKind) {
        cout << "printVARIABLEAttribution" << endl;
        //ErrorManager::printVectorAttribution(variableKey, attributionKey, lineNumber);
        return;
    }
    //Verifies ERR_CHAR_TO_X
    if (attributionNode->sType == charSType && resultVariable.valueFound.type != charSType) {
        cout << "printCharToXAttribution" << endl;
        //ErrorManager::printCharToXAttribution(variableKey, attributionKey, resultVariable.valueFound.type, lineNumber);
        return;
    }
    //Verifies ERR_STRING_VECTOR
    if (resultVariable.valueFound.type == stringSType) {
        cout << "ERR_STRING_VECTOR" << endl;
        return;
    }

    //Verifies ERR_STRING_TO_X
    if (attributionNode->sType == stringSType) {
        cout << "printStringToXAttribution" << endl;
        //ErrorManager::printStringToXAttribution(variableKey, attributionKey,  resultVariable.valueFound.type, lineNumber);
        return;
    }

    //Verifies ERR_WRONG_TYPE
    if (this->verifyCoersion(resultVariable.valueFound.type, attributionNode->sType) != SUCCESS) {
        
        cout << "printWrongTypeAttribution" << endl;
        //ErrorManager::printWrongTypeAttribution(variableKey, attributionKey, 
        //resultVariable.valueFound.type, 
        //resultAttribution.valueFound.type, lineNumber);
        return;
    }

    variableNode->sType = resultVariable.valueFound.type;
    attributionSymbolNode->sType = resultVariable.valueFound.type;
    indexerSymbolNode->sType = resultVariable.valueFound.type;

}

void SymbolTableStack::makeInput(AST *inputNode, AST *identifierNode) {
    
    string variableKey = string(identifierNode->value->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);

    //Verifies ERR_UNDECLARED
    if (!resultVariable.found) {
        cout << "element not found" << endl;
        //ErrorManager::printElementNotFoundAttribution(variableKey, attributionKey, variableKey, lineNumber);
        return;
    }

    SyntacticalType typeFound = resultVariable.valueFound.type;
    
    //Verifies ERR WRONG PAR INPUT
    if (typeFound != intSType && typeFound != floatSType) {
        cout << "ERR WRONG PAR INPUT" << endl;
        return;
    }

    inputNode->sType = typeFound;
    identifierNode->sType = typeFound;

}

void SymbolTableStack::makeOutputIdentifier(AST *outputNode, AST *identifierNode) {
    
    string variableKey = string(identifierNode->value->literalTokenValueAndType.value.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);

    //Verifies ERR_UNDECLARED
    if (!resultVariable.found) {
        cout << "element not found" << endl;
        //ErrorManager::printElementNotFoundAttribution(variableKey, attributionKey, variableKey, lineNumber);
        return;
    }

    SyntacticalType typeFound = resultVariable.valueFound.type;
    
    //Verifies ERR WRONG PAR INPUT
    if (typeFound != intSType && typeFound != floatSType) {
        cout << "ERR WRONG PAR OUTPUT" << endl;
        return;
    }

    outputNode->sType = typeFound;
    identifierNode->sType = typeFound;

}

void SymbolTableStack::makeOutputLiteral(AST *outputNode, AST *literalNode) {
    
    SyntacticalType typeFound = literalNode->sType;
    
    //Verifies ERR WRONG PAR INPUT
    if (typeFound != intSType && typeFound != floatSType) {
        cout << "ERR WRONG PAR OUTPUT" << endl;
        return;
    }

    outputNode->sType = typeFound;
    literalNode->sType = typeFound;

}

void SymbolTableStack::makeShift(AST *shiftSumbolNode, AST *shiftLiteralNode) {
    
    int intValue = shiftLiteralNode->value->literalTokenValueAndType.value.integerValue;
    
    //Verifies ERR WRONG PAR SHIFT
    if (intValue > 16) {
        cout << "ERR WRONG PAR SHIFT" << endl;
        return;
    }

    shiftSumbolNode->sType = intSType;
    shiftLiteralNode->sType = intSType;
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
    return "";
}

void SymbolTableStack::insertLiteral(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {
    
    string key = this->stringFromLiteralValue(lexicalValue->literalTokenValueAndType);
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
    if (this->find(key).found) { 
        cout << "Não foi possível declarar. Funcao já declarada" << endl;
        return; 
    }
    //Verifies ERR FUNCTION STRING
    if (sType == stringSType) {
        cout << "ERR FUNCTION STRING" << endl;
        return; //nao insere dai?
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
        cout << "ERR WRONG PAR RETURN" << endl;
        return;
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
            //TODO: tira da tabela???
            this->variablesWithPendantTypes.pop_front();
            continue;
        }
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