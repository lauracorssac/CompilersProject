/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "CodeGenerator.hpp"
#include "Utils.hpp"
#include <string>
#include <list>
#include "AST.hpp"
#include "Code.hpp"

using namespace std;

CodeGenerator::CodeGenerator() { 
    this->registerNumber = 0;
    this->labelNumber = 0;
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

    int nodeValue = integerFromLiteralValue(literalNode->value->literalTokenValueAndType);
    int registerValue = this->getRegister();
    CodeOperand leftOperand = {.operandType=number, .numericalValue=nodeValue};
    CodeOperand rightOperand = {.operandType=_register, .numericalValue=registerValue};
    
    list<CodeOperand> rightList; 
    rightList.push_back(rightOperand);
    list<CodeOperand> leftList; 
    leftList.push_back(leftOperand);

    Code code = { .instructionType=loadI, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    list<Code> codeList;
    codeList.push_back(code);
    literalNode->code = codeList;
  
}

//Exemplo: addI rsp, 4 => rsp
void CodeGenerator::makeLocalVariableDeclaration(AST *variableNode) {
    
    CodeOperand rspOperand = {.operandType=_register, .numericalValue=rsp};
    CodeOperand fourOperand = {.operandType=number, .numericalValue=4};

    list<CodeOperand> leftList; 
    leftList.push_back(rspOperand);
    leftList.push_back(fourOperand);

    list<CodeOperand> rightList; 
    rightList.push_back(rspOperand);
    
    Code code = { .instructionType=addI, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    list<Code> codeList;
    codeList.push_back(code);
    variableNode->code = codeList;
}

//Exemplo: storeAI r0 => rfp, 0
//Memoria(rfp + 0) = r0
void CodeGenerator::makeAttributionLocalVariable(AST *variableNode, AST *attSymbolNode, AST *attributionNode, int offset, VariableType varType) {

    int registerOrigin = attributionNode->code.front().leftOperands.front().numericalValue;
    CodeOperand leftOperand = {.operandType=_register, .numericalValue=registerOrigin};
    int registerDestination = varType == global ? rbss : rfp;
    CodeOperand rightOperand1 = {.operandType=_register, .numericalValue=registerDestination};
    CodeOperand rightOperand2 = {.operandType=number, .numericalValue=offset};
    
    list<CodeOperand> leftList; 
    leftList.push_back(leftOperand);
    list<CodeOperand> rightList; 
    rightList.push_back(rightOperand1);
    rightList.push_back(rightOperand2);

    Code code = { .instructionType=storeAI, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    list<Code> codeList;
    codeList.insert(codeList.end(), variableNode->code.begin(), variableNode->code.end());
    codeList.insert(codeList.end(), attributionNode->code.begin(), attributionNode->code.end());
    codeList.push_back(code);

    attSymbolNode->code = codeList;

}

