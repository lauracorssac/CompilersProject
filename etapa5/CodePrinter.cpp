/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "CodePrinter.hpp"
#include "AST.hpp"
#include "Code.hpp"
#include <list>
#include <iostream>

using namespace std;

CodePrinter::CodePrinter() { }

void CodePrinter::printTree(void *tree) {

    AST *rootNode = (AST *) tree;

    list<Code>::iterator it;

    for (it = rootNode->code.begin(); it != rootNode->code.end(); ++it) {

        printInstructionType(it->instructionType);
        cout << " ";
        printOperands(it->leftOperands);
        cout << " => ";
        printOperands(it->rightOperands);
        cout << endl;
    }
    
}

void CodePrinter::printOperands(list<CodeOperand> operands) {

    list<CodeOperand>::iterator it;
    for (it = operands.begin(); it != operands.end(); ++it) {
        this->printOperand(*it);
        cout << ", ";
    }

}

void CodePrinter::printOperand(CodeOperand operand) {

    string numbericalValueString = to_string(operand.numericalValue);
    switch (operand.operandType) {
    case _register:
        cout << "r" << numbericalValueString;
        break;
    case label:
        cout << "L" << numbericalValueString << ":";
        break;
    case number:
        cout << numbericalValueString << ":";
        break;
    default:
        break;
    }

}

void CodePrinter::printInstructionType(InstructionType type) {

    switch (type)
    {
    case nop:
    cout << "nop";
        break;
    case add:
        cout << "add";
        break;
    case sub:
        cout << "sub";
		break;
    case mult:
        cout << "mult";
		break;
    case _div:
        cout << "div";
		break;
    case addI:
        cout << "addI";
		break;
    case subI:
        cout << "subI";
		break;
    case rsubI:
        cout << "rsubI";
		break;
    case multI:
        cout << "multI";
		break;
    case divI:
        cout << "divI";
		break;
    case rdivI:
        cout << "rdivI";
		break;
    case lshift:
        cout << "lshift";
		break;
    case lshiftI:
        cout << "lshiftI";
		break;
    case rshift:
        cout << "rshift";
		break;
    case rshiftI:
        cout << "rshiftI";
		break;
    case _and:
        cout << "and";
		break;
    case andI:
        cout << "andI";
		break;
    case _or:
        cout << "or";
		break;
    case orI:
        cout << "orI";
		break;
    case _xor:
        cout << "xor";
		break;
    case xorI:
        cout << "xorI";
		break;
    case load:
        cout << "load";
		break; 
    case loadI:
        cout << "loadI";
		break; 
    case loadAI:
        cout << "loadAI";
		break; 
    case loadAO:
        cout << "loadAO";
		break; 
    case cload:
        cout << "cload";
		break;
    case cloadAI:
        cout << "cloadAI";
		break;
    case cloadAO:
        cout << "cloadAO";
		break;
    case store:
        cout << "store";
		break; 
    case storeAI:
        cout << "storeAI";
		break; 
    case storeAO:
        cout << "storeAO";
		break; 
    case cstore:
        cout << "cstore";
		break; 
    case cstoreAI:
        cout << "cstoreAI";
		break; 
    case cstoreAO:
        cout << "cstoreAO";
		break; 
    case i2i:
        cout << "i2i";
		break;
    case c2c:
        cout << "c2c";
		break;
    case c2i:
        cout << "c2i";
		break;
    case i2c:
        cout << "i2c";
		break;
    case jump:
        cout << "jump";
		break;
    case jumpI:
        cout << "jumpI";
		break;
    case cbr:
        cout << "cbr";
		break;
    case cmp_LT:
        cout << "cmp_LT";
		break;
    case cmp_LE:
        cout << "cmp_LE";
		break;
    case cmp_EQ:
        cout << "cmp_EQ";
		break;
    case cmp_GE:
        cout << "cmp_GE";
		break;
    case cmp_GT:
        cout << "cmp_GT";
		break;
    case cmp_NE:
        cout << "cmp_NE";
		break;
    case halt:
        cout << "halt";
		break;
    }

}