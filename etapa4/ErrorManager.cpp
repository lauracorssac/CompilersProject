/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTableValue.hpp"
#include "ErrorManager.hpp"

#include <string>
#include <iostream>

using namespace std;

void ErrorManager::printStringVector(string variableKey) {
    cout << "Variável " << variableKey << " não pode ser declarada." << endl;
    cout << "Motivo: Não é permitido declaração de vetores de string." << endl;
}

void ErrorManager::printDeclaredVariableInitialization(string variableKey, SymbolTableValue valueFound, int line) {
    cout << "Não foi possível declarar " << variableKey << endl;
    cout << "Motivo: Esse nome já foi declarado na linha " << valueFound.line << endl;
}

void ErrorManager::printAttributionError(string variableKey, string attributionKey, int line) {

    cout << "Não foi possível fazer atribuição de " << attributionKey << 
    " para " << variableKey << " na linha " << to_string(line) << endl;
}

void ErrorManager::printElementsNotFoundAttribution(string variableKey, string attributionKey, int line) {
    ErrorManager::printAttributionError(variableKey, attributionKey, line);
    cout << "Motivo: Nenhum dos elementos foram declarados.";
}
void ErrorManager::printElementNotFoundAttribution(string variableKey, string attributionKey, string undeclared, int line) {
    ErrorManager::printAttributionError(variableKey, attributionKey, line);
    cout << "Motivo: " << undeclared  << " não foi declarado " << endl;
}
void ErrorManager::printStringToXAttribution(string variableKey, string attributionKey,
 SyntacticalType variableType, int line) {
    ErrorManager::printAttributionError(variableKey, attributionKey, line);
    cout << "Motivo: " << attributionKey  << " é uma string e strings não podem ser convertidas a nenhum tipo. No caso, " << variableKey << " é um ";
    printSyntacticalType(variableType);
    cout << endl;
}

void ErrorManager::printCharToXAttribution(string variableKey, string attributionKey,
 SyntacticalType variableType, int line) {
    ErrorManager::printAttributionError(variableKey, attributionKey, line);
    cout << "Motivo: " << attributionKey  << " é um char e char não podem ser convertidos a nenhum tipo. No caso, " << variableKey << " é um ";
    printSyntacticalType(variableType);
    cout << endl;
}

void ErrorManager::printFunctionAttribution(string variableKey, string attributionKey, int line) {
    ErrorManager::printAttributionError(variableKey, attributionKey, line);
    cout << "Motivo: " << variableKey  << " é uma função e não pode receber valor" << endl;
}

void ErrorManager::printVectorAttribution(string variableKey, string attributionKey, int line) {
    ErrorManager::printAttributionError(variableKey, attributionKey, line);
    cout << "Motivo: " << variableKey  << " é um vetor e não pode receber valor" << endl;
}

void ErrorManager::printWrongTypeAttribution(string variableKey, string attributionKey,
SyntacticalType variableType, SyntacticalType attributionType, int line) {
    ErrorManager::printAttributionError(variableKey, attributionKey, line);
    cout << "Motivo: " << attributionKey  << " possui tipo = ";
    printSyntacticalType(attributionType);
    cout << " e não pode ser convertido para ";
    printSyntacticalType(variableType);
    cout << endl;
}