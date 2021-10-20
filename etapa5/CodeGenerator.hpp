/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

using namespace std;
#include <string>
#include "AST.hpp"
#include "Code.hpp"

class CodeGenerator
{
private:
    int registerNumber;
    int getRegister();
    int labelNumber;
    int getLabel();
    bool mainWasDeclared;
    InstructionCode makeOffsetLocalVariables(int offset);
public:
    CodeGenerator();
    void makeLiteralCode(AST *literalNode);
    void makeAttributionLocalVariable(AST *attSymbolNode, AST *attributionNode, OffsetAndScope offsetAndScope);
    void makeFunction(AST *functionNode, AST *nextNode, int offset);
    void appendCode(AST *parent, AST*child);
    void makeBinaryOperation(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    
};


#endif