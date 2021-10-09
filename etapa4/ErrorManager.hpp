/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef ERRORMANAGER_HPP
#define ERRORMANAGER_HPP

#include "SymbolTableValue.hpp"
#include <string>

extern "C" {
    #include "AST.h"
}

using namespace std;

class ErrorManager {
public:
    static void printLine(int line);
    static string stringFromExpression(AST *expressionNode);
    static void printAttributionErrorExpression(string variableKey);
    static void printAttributionError(string variableKey, string attributionKey);
    static void errorStringVector(string variableKey);
    static void errorDeclared(string variableKey, SymbolTableValue valueFound);
    static void errorElementNotFound(string undeclared);
    static void errorStringToX(string variableKey, string attributionKey, SyntacticalType variableType);
    static void errorCharToX(string variableKey, AST *attributionNode, SyntacticalType variableType);
    static void errorFunctionVector(string variableKey);
    static void errorFunctionVariable(string variableKey);
    static void errorVectorFunction(string variableKey);
    static void errorVectorVariable(string variableKey);
    static void errorVariableFunction(string variableKey);
    static void errorVariableVector(string variableKey);
    static void errorWrongType(AST *attributionNode, SyntacticalType expectedType);
    static void errorInput(AST *inputNode);
    static void errorOutput(AST *outputNode);
    static void errorShift(AST *shiftNode);
};

#endif