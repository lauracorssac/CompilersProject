/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

using namespace std;
#include <string>
#include "AST.hpp"

class CodeGenerator
{
private:
    int registerNumber;
    int getRegister();
    int labelNumber;
    int getLabel();

public:
    CodeGenerator();
    void makeLiteralCode(AST *literalNode);
    void makeAttributionLocalVariable(AST *variableNode, AST *attSymbolNode, AST *attributionNode, 
    int offset, VariableType varType);
    void makeLocalVariableDeclaration(AST *variableNode);
};


#endif