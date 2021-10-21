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
    InstructionCode makeNop(int label);
    void appendCode(AST *parent, list<InstructionCode> newCode);
    list<InstructionCode> makeCompare(CodeOperand r1Operand, CodeOperand labelTrue, CodeOperand labelFalse);
    InstructionCode makeCBR(CodeOperand r3Operand, CodeOperand labelTrue, CodeOperand labelFalse);
    list<InstructionCode> makeCMPGE(CodeOperand r1Operand, CodeOperand r3Operand);
    void coverPatchworks(list<InstructionCode> &code, CodeOperand labelOperand, bool patchworkType);
    InstructionCode loadConstant(int constant, CodeOperand registerDestination);


public:
    CodeGenerator();
    void makeLiteralCode(AST *literalNode);
    void makeAttributionLocalVariable(AST *attSymbolNode, AST *attributionNode, OffsetAndScope offsetAndScope);
    void makeFunction(AST *functionNode, AST *nextNode, int offset);
    void appendCode(AST *parent, AST*child);
    void makeBinaryOperation(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    void makeAnd(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    
    //aka remenda
    void coverPatchworks(AST *node, CodeOperand labelOperand, bool patchworkType);
    list<InstructionCode> createBoolFlow(AST *node, CodeOperand destinationLabel, CodeOperand destinationRegister);
    InstructionCode loadBooleanCode(bool boolean, CodeOperand registerDestination);
    


    
};


#endif