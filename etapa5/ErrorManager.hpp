/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef ERRORMANAGER_HPP
#define ERRORMANAGER_HPP

#include "SymbolTableValue.hpp"
#include <string>

#include "AST.hpp"
extern "C" {
    
}

using namespace std;

class ErrorManager {
public:
    static void printLine(int line);
    static string stringFromExpression(AST *expressionNode);
    static void printAttributionError(string variableKey, AST *attributionNode);
    static void errorStringVector(string variableKey);
    static void errorDeclared(string variableKey, SymbolTableValue valueFound);
    static void errorElementNotFound(string undeclared);
    static void errorStringToX(string variableKey, AST *attributionNode, SyntacticalType variableType);
    static void errorCharToX(string variableKey, AST *attributionNode, SyntacticalType variableType);
    static void errorCharOrStringToXOperation(AST *expressionNode, SyntacticalType type);
    static void errorFunctionVector(string variableKey);
    static void errorFunctionVariable(string variableKey);
    static void errorVectorFunction(string variableKey);
    static void errorVectorVariable(string variableKey);
    static void errorVariableFunction(string variableKey);
    static void errorVariableVector(string variableKey);
    static void errorWrongType(AST *attributionNode, SyntacticalType expectedType);
    static void errorInput(AST *inputNode);
    static void errorOutput(AST *outputNode);
    static void errorShift(AST *shiftWrongNode);
    static void errorFunctionString(AST *functionNode);
    static void errorReturn(AST *returnNode, string functionName, SyntacticalType functionType, int functionLine);
    static void errorFunctionStringParameter(string parameterName);
    static void errorFunctionStringFunction(AST *functionNode);
    static void errorWrongQuantityParameters(AST *functionNode, int expectedQuantity, int givenQuantity);
    static void errorWrongTypeParameters(AST *functionNode, SyntacticalType expectedType, int position, AST *givenParameter);
    static void errorMaxString(AST *variableNode, AST *attributionNode, int variableSize);
    static void errorException();
    static void shutDown(int errorCode);
    static void doubleDeclarationOfMain();
    static void noDeclarationOfMain();
};

#endif