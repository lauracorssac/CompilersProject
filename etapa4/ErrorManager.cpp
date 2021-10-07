/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTableValue.hpp"
#include "ErrorManager.hpp"

#include <string>
#include <iostream>

extern "C" {
    #include "errors.h"
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
    cout << "Variável " << variableKey << " não pode ser declarada." << endl;
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

void ErrorManager::errorCharToX(string variableKey, string attributionKey, SyntacticalType variableType) {
    cout << "Motivo: " << attributionKey  << " é do tipo char, que não pode ser convertido em nenhum tipo. No caso, " << variableKey << " é um ";
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

void ErrorManager::errorWrongTypeNamed(string attributionKey, SyntacticalType expectedType, SyntacticalType givenType) {

    cout << attributionKey  << " possui tipo = ";
    printSyntacticalType(givenType);
    cout << " e não pode ser convertido para o tipo esperado = ";
    printSyntacticalType(expectedType);
    cout << endl;

    exit(ERR_WRONG_TYPE);
}

void ErrorManager::errorWrongTypeExpression(SyntacticalType expectedType, SyntacticalType givenType) {

    cout << "Expressão possui tipo = ";
    printSyntacticalType(givenType);
    cout << " e não pode ser convertido para o tipo esperado = ";
    printSyntacticalType(expectedType);
    cout << endl;

    exit(ERR_WRONG_TYPE);
}