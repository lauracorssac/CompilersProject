/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef ERRORMANAGER_HPP
#define ERRORMANAGER_HPP

#include "SymbolTableValue.hpp"
#include <string>
using namespace std;

class ErrorManager {
public:
    static void printLine(int line);
    static void printAttributionErrorExpression(string variableKey);
    static void printAttributionError(string variableKey, string attributionKey);
    static void errorStringVector(string variableKey);
    static void errorDeclared(string variableKey, SymbolTableValue valueFound);
    static void errorElementNotFound(string undeclared);
    static void errorStringToX(string variableKey, string attributionKey, SyntacticalType variableType);
    static void errorCharToX(string variableKey, string attributionKey, SyntacticalType variableType);
    static void errorFunctionVector(string variableKey);
    static void errorFunctionVariable(string variableKey);
    static void errorVectorFunction(string variableKey);
    static void errorVectorVariable(string variableKey);
    static void errorVariableFunction(string variableKey);
    static void errorVariableVector(string variableKey);
    static void errorWrongTypeNamed(string attributionKey, SyntacticalType expectedType, SyntacticalType givenType);
    static void errorWrongTypeExpression(SyntacticalType expectedType, SyntacticalType givenType);
};

#endif