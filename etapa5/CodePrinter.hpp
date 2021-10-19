/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef CODE_PRINTER_HPP
#define CODE_PRINTER_HPP

#include "AST.hpp"

class CodePrinter {

private:
void printInstructionType(InstructionType type);
void printOperands(list<CodeOperand> operands);
void printOperand(CodeOperand operand);

public:
void printTree(AST *rootNode);



};



#endif