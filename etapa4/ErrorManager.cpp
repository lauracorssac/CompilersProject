/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTableValue.hpp"
#include "ErrorManager.hpp"
#include "Utils.hpp"

#include <string>
#include <iostream>
#include <cctype>

extern "C" {
    #include "errors.h"
    #include "AST.h"
    #include "LexicalValue.h"
}

using namespace std;

void ErrorManager::printLine(int line) {
    cout << "ERRO linha: " << line << endl;
}

void ErrorManager::printAttributionErrorExpression(string variableKey) {
    cout << "Não foi possível fazer atribuição de expressão para " << variableKey << endl;
}

void ErrorManager::printAttributionError(string variableKey, string attributionKey) {
    cout << "Não foi possível fazer atribuição de " << attributionKey << " para " << variableKey << endl;
}

void ErrorManager::errorStringVector(string variableKey) {
    cout << "Vetor " << variableKey << " não pode ser declarado." << endl;
    cout << "Motivo: Não é permitido declaração de vetores de string." << endl;
    exit(ERR_STRING_VECTOR);
}

void ErrorManager::errorDeclared(string variableKey, SymbolTableValue valueFound) {
    cout << "Não foi possível declarar " << variableKey << endl;
    cout << "Nome já foi declarado na linha " << valueFound.line << endl;
    exit(ERR_DECLARED);
}

// void ErrorManager::printElementsNotFoundAttribution(string variableKey, string attributionKey, int line) {
//     ErrorManager::printAttributionError(variableKey, attributionKey, line);
//     cout << "Motivo: Nenhum dos elementos foram declarados.";
// }

void ErrorManager::errorElementNotFound(string undeclared) {
    cout << undeclared  << " não foi declarado " << endl;
    exit(ERR_UNDECLARED);
}

void ErrorManager::errorStringToX(string variableKey, string attributionKey,
 SyntacticalType variableType) {
    cout << attributionKey  << " é do tipo string, que não pode ser convertido em nenhum tipo. No caso, " << variableKey << " é um ";
    printSyntacticalType(variableType);
    cout << endl;
    exit(ERR_STRING_TO_X);
    
}

string ErrorManager::stringFromExpression(AST *expressionNode) {
   
    if (expressionNode->value->tokenType == literalType || expressionNode->value->tokenType == identifierType) {
        return stringFromLiteralValue(expressionNode->value->literalTokenValueAndType);
    } else {
       return "Expressão";
    }
}

void ErrorManager::errorCharToX(string variableKey, AST *attributionNode, SyntacticalType variableType) {

    string element = ErrorManager::stringFromExpression(attributionNode);
    cout << element  << " é do tipo char, que não pode ser convertido em nenhum tipo. No caso, " << variableKey << " é um ";
    printSyntacticalType(variableType);
    cout << endl;
    exit(ERR_CHAR_TO_X);
}

void ErrorManager::errorFunctionVector(string variableKey) {
    cout << variableKey  << " é uma função e está sendo usada como vetor" << endl;
    exit(ERR_FUNCTION);
}

void ErrorManager::errorFunctionVariable(string variableKey) {
    cout << variableKey  << " é uma função e está sendo usada como variável" << endl;
    exit(ERR_FUNCTION);
}

void ErrorManager::errorVectorFunction(string variableKey) {
    cout << variableKey  << " é um vetor e está sendo usada como função" << endl;
    exit(ERR_VECTOR);
}

void ErrorManager::errorVectorVariable(string variableKey) {
    cout << variableKey  << " é um vetor e está sendo usada como variável" << endl;
    exit(ERR_VECTOR);
}

void ErrorManager::errorVariableFunction(string variableKey) {
    cout << variableKey  << " é uma variável e está sendo usada como função" << endl;
    exit(ERR_VARIABLE);
}

void ErrorManager::errorVariableVector(string variableKey) {
    cout << variableKey  << " é uma variável e está sendo usada como vetor" << endl;
    exit(ERR_VARIABLE);
}

void ErrorManager::errorWrongType(AST *attributionNode, SyntacticalType expectedType) {

    string element = ErrorManager::stringFromExpression(attributionNode);
    cout << element; 
    cout << " possui tipo = ";
    printSyntacticalType(attributionNode->sType);
    cout << " e não pode ser convertido para o tipo esperado = ";
    printSyntacticalType(expectedType);
    cout << endl;

    exit(ERR_WRONG_TYPE);
}

void ErrorManager::errorInput(AST *inputNode) {

    string element = ErrorManager::stringFromExpression(inputNode);
    cout << element << " não pode seguir comando input, pois possui tipo = ";
    printSyntacticalType(inputNode->sType);
    cout << " e esse comando somente aceita valores do tipo int e float." << endl;

    exit(ERR_WRONG_PAR_INPUT);
}

void ErrorManager::errorOutput(AST *outputNode) {

    string element = ErrorManager::stringFromExpression(outputNode);
    cout << element << " não pode seguir comando output, pois possui tipo = ";
    printSyntacticalType(outputNode->sType);
    cout << " e esse comando somente aceita valores do tipo int e float." << endl;

    exit(ERR_WRONG_PAR_OUTPUT);
}

void ErrorManager::errorShift(AST *shiftNode) {
    string element = ErrorManager::stringFromExpression(shiftNode);
    cout << "Não é possível realizar a operação de shift com " << element << ", pois ele possui valor maior que 16" << endl;
    
    exit(ERR_WRONG_PAR_SHIFT);
}

void ErrorManager::errorFunctionString(AST *functionNode) {

    string element = stringFromLiteralValue(functionNode->value->literalTokenValueAndType);
    cout << "Função " << element;
    cout << " não pode ser declarada, pois possui tipo string e isso não é permitido nessa linguagem" << endl;
    
    exit(ERR_FUNCTION_STRING);
}

void ErrorManager::errorReturn(AST *returnNode, string functionName, SyntacticalType functionType, int functionLine) {

    string element = ErrorManager::stringFromExpression(returnNode);
    cout << element << " não pode ser suceder o comando return";
    cout << ", pois possui tipo = ";
    printSyntacticalType(returnNode->sType);
    cout << ", não compatível com o esperado pela função " <<  functionName;
    cout << ", declarada na linha " << functionLine << " com tipo = ";
    printSyntacticalType(functionType);
    cout << endl;
    
    exit(ERR_WRONG_PAR_RETURN);
}

void ErrorManager::errorFunctionStringParameter(string parameterName) {

    cout << parameterName << " não pode ser parâmetro de uma função, pois possui tipo string" << endl;
    
    exit(ERR_FUNCTION_STRING);
}

void ErrorManager::errorFunctionStringFunction(AST *functionNode) {

    string element = ErrorManager::stringFromExpression(functionNode);
    cout << element << " não pode ser declarada como uma função, pois possui tipo string" << endl;
    exit(ERR_FUNCTION_STRING);
}

void ErrorManager::errorWrongQuantityParameters(AST *functionNode, int expectedQuantity, int givenQuantity) {

    string element = ErrorManager::stringFromExpression(functionNode);
    int line = functionNode->value->lineNumber;

    cout << "Função " << element << " declarada na linha " << line << " espera " << expectedQuantity 
    << " parâmetros, mas recebeu " << givenQuantity << endl;

    if (expectedQuantity > givenQuantity) {
        exit(ERR_MISSING_ARGS);
    } else {
        exit(ERR_EXCESS_ARGS);
    }

}

void ErrorManager::errorWrongTypeParameters(AST *functionNode, SyntacticalType expectedType, int position, AST *givenParameter) {

    string element = ErrorManager::stringFromExpression(functionNode);
    string parameterName = ErrorManager::stringFromExpression(givenParameter);
    SyntacticalType givenType = givenParameter->sType;
    int line = functionNode->value->lineNumber;

    cout << "Função " << element << " declarada na linha " << line << " espera um parâmetro do tipo ";
    printSyntacticalType(expectedType);
    cout << " na posição " << position
    << ", mas recebeu " << parameterName << ", que possui tipo ";
    printSyntacticalType(givenType);
    cout << ", que não pode ser convertido para ";
    printSyntacticalType(expectedType);
    cout << endl;

    exit(ERR_WRONG_TYPE_ARGS);
}