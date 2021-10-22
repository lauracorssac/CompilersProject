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
    void prependCode(AST *node, list<InstructionCode> newCode);
    list<InstructionCode> makeCompare(CodeOperand r1Operand, CodeOperand labelTrue, CodeOperand labelFalse);
    InstructionCode makeCBR(CodeOperand r3Operand, CodeOperand labelTrue, CodeOperand labelFalse);
    list<InstructionCode> makeCMPGE(CodeOperand r1Operand, CodeOperand r3Operand);
    void coverPatchworks(list<InstructionCode> &code, CodeOperand labelOperand, bool patchworkType);
    InstructionCode loadConstant(int constant, CodeOperand registerDestination);
    InstructionCode makeBinaryInstruction(InstructionType instructionType, int prefixLabel, CodeOperand r1Operand, CodeOperand r2Operand, CodeOperand r3Operand);
    InstructionCode makeStoreCode(int prefixLabel, CodeOperand op1, CodeOperand op2, CodeOperand op3);
    InstructionCode makeJumpInstruction(CodeOperand destinationLabel);
    InstructionCode makeHalt();
    list<InstructionCode> makeInitialCode(int preliminaryCodeSize);

public:
    CodeGenerator();
    void makeLiteralCode(AST *literalNode);
    void makeAttributionLocalVariable(AST *attSymbolNode, AST *attributionNode, OffsetAndScope offsetAndScope);
    void makeFunction(AST *functionNode, AST *nextNode, int offset);
    void appendCode(AST *parent, AST*child);
    void makeBinaryOperation(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    void makeAnd(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    void makeOr(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode);
    void makeIf(AST *ifNode, AST *expNode, AST *ifBlockNode, AST *elseBlockNode);
    void makeWhile(AST *whileNode, AST *expNode, AST *whileBlockNode);
    void makeFor(AST *forNode, AST *att1Node, AST *expNode, AST *att2Node, AST *forBlockNode);
    void makeDeclaredVariable(AST *variableNode, OffsetAndScope offsetAndScope);
    
    //aka remenda
    void coverPatchworks(AST *node, CodeOperand labelOperand, bool patchworkType);
    list<InstructionCode> createBoolFlow(AST *node, int destinationLabel, CodeOperand destinationRegister);
    InstructionCode loadBooleanCode(bool boolean, CodeOperand registerDestination);

    void generateFinalCode(AST *finalTree);
    void generateInitialCode(AST *finalTree);
    
};


#endif