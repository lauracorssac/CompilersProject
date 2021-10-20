/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "CodeGenerator.hpp"
#include "ErrorManager.hpp"
#include "Utils.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <list>
#include "AST.hpp"
#include "Code.hpp"

using namespace std;

CodeGenerator::CodeGenerator() { 
    this->registerNumber = 0;
    this->labelNumber = 1;
    this->mainWasDeclared = false;
}

int CodeGenerator::getRegister() {
    
    // increment registerNumber after use
    return this->registerNumber++;
}

int CodeGenerator::getLabel() {
    
    // increment labelNumber after use
    return this->labelNumber++;
}

//Exemplo: loadI 34 => r0
void CodeGenerator::makeLiteralCode(AST *literalNode) {

    cout << "makeLiteralCode" << endl;
    int nodeValue = integerFromLiteralValue(literalNode->value->literalTokenValueAndType);
    int registerValue = this->getRegister();

    CodeOperand leftOperand = {.operandType=number, .numericalValue=nodeValue};
    CodeOperand rightOperand = {.operandType=_register, .numericalValue=registerValue};
    
    list<CodeOperand> rightList; 
    rightList.push_back(rightOperand);
    list<CodeOperand> leftList; 
    leftList.push_back(leftOperand);

    InstructionCode code = { .prefixLabel= -1, 
    .instructionType=loadI, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    list<InstructionCode> codeList;
    codeList.push_back(code);
    
    literalNode->code = codeList;
    literalNode->resultRegister = rightOperand;

    cout << "makeLiteralCode" << endl;
  
}

//Exemplo: addI rsp, 4 => rsp
InstructionCode CodeGenerator::makeOffsetLocalVariables(int offset) {
    
    CodeOperand rspOperand = {.operandType=registerPointer, .numericalValue=rsp};
    CodeOperand fourOperand = {.operandType=number, .numericalValue=offset};

    list<CodeOperand> leftList; 
    leftList.push_back(rspOperand);
    leftList.push_back(fourOperand);

    list<CodeOperand> rightList; 
    rightList.push_back(rspOperand);
    
    InstructionCode code = { .prefixLabel= -1, 
    .instructionType=addI, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    return code;
}

//Exemplo: storeAI r0 => rfp, 0
//Memoria(rfp + 0) = r0
void CodeGenerator::makeAttributionLocalVariable(AST *attSymbolNode, 
AST *attributionNode, OffsetAndScope offsetAndScope) {

    CodeOperand leftOperand =  attributionNode->resultRegister;
    int registerDestination = (offsetAndScope.scope == global) ? rbss : rfp;
    cout << "scope makeAttributionLocalVariable = " << offsetAndScope.scope;
    CodeOperand rightOperand1 = {.operandType=registerPointer, .numericalValue=registerDestination};
    CodeOperand rightOperand2 = {.operandType=number, .numericalValue=offsetAndScope.offset};
    
    list<CodeOperand> leftList; 
    leftList.push_back(leftOperand);
    list<CodeOperand> rightList; 
    rightList.push_back(rightOperand1);
    rightList.push_back(rightOperand2);

    InstructionCode code = { .prefixLabel= -1, 
    .instructionType=storeAI, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    list<InstructionCode> codeList;
    codeList.insert(codeList.end(), attributionNode->code.begin(), attributionNode->code.end());
    codeList.push_back(code);
    //codeList.insert(codeList.end(), nextNode->code.begin(), nextNode->code.end());


    attSymbolNode->code = codeList;

}

//L0: nop
void CodeGenerator::makeFunction(AST *functionNode, AST *nextNode, int offset) {

    int _label;
    string functionName = stringFromLiteralValue(functionNode->value->literalTokenValueAndType);
    
    if (strcmp(functionName.c_str(), "main") == 0) {
        if (this->mainWasDeclared) { ErrorManager::doubleDeclarationOfMain(); }
        this->mainWasDeclared = true;
        _label = 0;
    } else {
        _label = this->labelNumber++;
    }

    list<CodeOperand> leftList; 
    list<CodeOperand> rightList; 
    InstructionCode code = { .prefixLabel= _label,
    .instructionType=nop, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    InstructionCode offsetVariables = this->makeOffsetLocalVariables(offset);

    list<InstructionCode> codeList;
    codeList.push_back(code);
    codeList.push_back(offsetVariables);
    codeList.insert(codeList.end(), nextNode->code.begin(), nextNode->code.end());

    functionNode->code = codeList;

}

void CodeGenerator::makeBinaryOperation(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode) {

    int registerValue = this->getRegister();
    CodeOperand rightOperandInstruction = {.operandType=_register, .numericalValue=registerValue};

    list<CodeOperand> leftList; 
    list<CodeOperand> rightList; 

    leftList.push_back(leftOperandNode->resultRegister);
    leftList.push_back(rightOperandNode->resultRegister);
    rightList.push_back(rightOperandInstruction);

    InstructionCode code = {
        .prefixLabel =-1,
    .instructionType=symbolNode->nodeInstructionType, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    this->appendCode(symbolNode, leftOperandNode);
    this->appendCode(symbolNode, rightOperandNode);
    symbolNode->code.push_back(code);

    symbolNode->resultRegister = rightOperandInstruction;

}

void CodeGenerator::appendCode(AST *parent, AST*child) {

    cout << "appendCode" << endl;
    cout << "parent = " << stringFromLiteralValue(parent->value->literalTokenValueAndType) << endl;
    //cout << "child = " << stringFromLiteralValue(parent->value->literalTokenValueAndType) << endl;
    list<InstructionCode> codeList;
    codeList.insert(codeList.end(), parent->code.begin(), parent->code.end());
    
    if (child != NULL ) {
        codeList.insert(codeList.end(), child->code.begin(), child->code.end());
    }
    
    parent->code = codeList;
    cout << "appendCode" << endl;
}
