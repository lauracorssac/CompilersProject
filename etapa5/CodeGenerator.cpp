/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "CodeGenerator.hpp"
#include "ErrorManager.hpp"
#include "CodePrinter.hpp"
#include "Utils.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <list>
#include "AST.hpp"
#include "Code.hpp"

using namespace std;
extern CodePrinter codePrinter;

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

list<InstructionCode> CodeGenerator::createBoolFlow(AST *node, int destinationLabel, CodeOperand destinationRegister) {

    list <CodeOperand> leftOperands;
    CodeOperand jumpDestinationLabel = {.operandType=label, .numericalValue=destinationLabel};
    leftOperands.push_back(jumpDestinationLabel);

    InstructionCode jumpInst = {.prefixLabel=-1,
    .instructionType=jumpI,
    .leftOperands= leftOperands,
    .rightOperands= list<CodeOperand>()
    };

    InstructionCode codeTrue = loadBooleanCode(true, destinationRegister);
    CodeOperand codeTrueLabel = {.operandType=label, .numericalValue=codeTrue.prefixLabel};
    coverPatchworks(node, codeTrueLabel, true);
    InstructionCode codeFalse = loadBooleanCode(false, destinationRegister);
    CodeOperand codeFalseLabel = {.operandType=label, .numericalValue=codeFalse.prefixLabel};
    coverPatchworks(node, codeFalseLabel, false);

    list<InstructionCode> code;
    code.push_back(codeTrue);
    code.push_back(jumpInst);
    code.push_back(codeFalse);
    code.push_back(jumpInst);

    return code;
}

void CodeGenerator::coverPatchworks(list<InstructionCode> &code, CodeOperand labelOperand, bool patchworkType) {

    CodeOperandType type = patchworkType ? patchworkTrue : patchworkFalse;

    for(auto instIt=code.rbegin(); instIt != code.rend(); instIt++) {

        for (auto opIt=instIt->rightOperands.rbegin(); opIt != instIt->rightOperands.rend(); opIt++) {
            if(opIt->operandType == type) {
                opIt->operandType = labelOperand.operandType;
                opIt->numericalValue = labelOperand.numericalValue;
            }
        }
    }

}

void CodeGenerator::coverPatchworks(AST *node, CodeOperand labelOperand, bool patchworkType) {

    this->coverPatchworks(node->code, labelOperand, patchworkType);
}

//Exeplo loadI constant => r2
InstructionCode CodeGenerator::loadConstant(int constant, CodeOperand registerDestination) {

    list<CodeOperand> leftList; 
    leftList.push_back({.operandType=number, .numericalValue=constant});
    list<CodeOperand> rightList; 
    rightList.push_back(registerDestination);

    int newLabel = getLabel();
    InstructionCode code = { .prefixLabel= -1, 
    .instructionType=loadI, 
    .leftOperands= leftList, 
    .rightOperands= rightList};
    return code;

}

//Exeplo loadI true => r2
InstructionCode CodeGenerator::loadBooleanCode(bool boolean, CodeOperand registerDestination) {

    list<CodeOperand> leftList; 
    leftList.push_back({.operandType=number, .numericalValue=boolean ? 1 : 0});
    list<CodeOperand> rightList; 
    rightList.push_back(registerDestination);

    int newLabel = getLabel();
    InstructionCode code = { .prefixLabel= newLabel, 
    .instructionType=loadI, 
    .leftOperands= leftList, 
    .rightOperands= rightList};
    return code;

}

//Exemplo: storeAI r0 => rfp, 0
//Exemplo: storeAI op1 => op2, op3
InstructionCode CodeGenerator::makeStoreCode(int prefixLabel, CodeOperand op1, CodeOperand op2, CodeOperand op3) {
    
    InstructionCode storeCode = { .prefixLabel= prefixLabel, 
    .instructionType=storeAI, 
    .leftOperands= {op1}, 
    .rightOperands= {op2, op3}};

    return storeCode;

}


//Exemplo: storeAI r0 => rfp, 0
//Memoria(rfp + 0) = r0
void CodeGenerator::makeAttributionLocalVariable(AST *attSymbolNode, 
AST *attributionNode, OffsetAndScope offsetAndScope) {

    CodeOperand leftOperand;
    int registerDestination = (offsetAndScope.scope == global) ? rbss : rfp;
    CodeOperand rightOperand1 = {.operandType=registerPointer, .numericalValue=registerDestination};
    CodeOperand rightOperand2 = {.operandType=number, .numericalValue=offsetAndScope.offset};
    int storeLabel;
    list<InstructionCode> codeList;

    if (attributionNode->hasPatchworks) {
        storeLabel = this->getLabel();
        int newRegister = getRegister();
        leftOperand = {.operandType=_register, .numericalValue=newRegister};
        list<InstructionCode> newCode = this->createBoolFlow(attributionNode, storeLabel, leftOperand);
        codeList.insert(codeList.end(), attributionNode->code.begin(), attributionNode->code.end());
        codeList.insert(codeList.end(), newCode.begin(), newCode.end());
    } else {
        storeLabel = -1;
        leftOperand = attributionNode->resultRegister;
        codeList.insert(codeList.end(), attributionNode->code.begin(), attributionNode->code.end());
    }

    InstructionCode storeCode = makeStoreCode(storeLabel, leftOperand, rightOperand1, rightOperand2);
   
    codeList.push_back(storeCode);
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
InstructionCode CodeGenerator::makeNop(int label) {

    InstructionCode nopCode = {.prefixLabel= label,
    .instructionType=nop, 
    .leftOperands= list<CodeOperand>(), 
    .rightOperands= list<CodeOperand>()};

    return nopCode;

}

//load 1 -> r2
//cmp_GE r1, r2 -> r3 // r3 = true se r1 >= r2, senão r3 = false
list<InstructionCode> CodeGenerator::makeCMPGE(CodeOperand r1Operand, CodeOperand r3Operand) {

    list<InstructionCode> code; 
    list<CodeOperand> leftList; 
    list<CodeOperand> rightList;

    int r2 = this->getRegister();
    CodeOperand r2Operand = {.operandType=_register, .numericalValue=r2}; //r2
    InstructionCode loadCode = this->loadConstant(1, r2Operand);
    code.push_back(loadCode);

    leftList.push_back(r1Operand); //r1
    leftList.push_back(r2Operand); //r2
    rightList.push_back(r3Operand); //r3

    InstructionCode compareCode = {.prefixLabel= -1,
    .instructionType=cmp_GE, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    code.push_back(compareCode);

    return code;

}

// cbr r3 -> labelTrue, labelFalse
InstructionCode CodeGenerator::makeCBR(CodeOperand r3Operand, CodeOperand labelTrue, CodeOperand labelFalse) {

    list<CodeOperand> leftList; 
    list<CodeOperand> rightList;

    leftList.push_back(r3Operand);
    rightList.push_back(labelTrue);
    rightList.push_back(labelFalse);

    InstructionCode code = {.prefixLabel= -1,
    .instructionType=cbr, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    return code;
}

// load 1 -> r2
// cmp_GE r1, r2 -> r3 
// cbr r3 -> labelTrue, labelFalse // PC = endereço(l2) se r1 = true, senão PC = endereço(l3)
list<InstructionCode> CodeGenerator::makeCompare(CodeOperand r1Operand, CodeOperand labelTrue, CodeOperand labelFalse) {

    int r3 = this->getRegister(); //r3
    CodeOperand r3Operand = {.operandType=_register, .numericalValue=r3};
    list<InstructionCode> code = this->makeCMPGE(r1Operand, r3Operand); 
    code.push_back(this->makeCBR(r3Operand, labelTrue, labelFalse));
    return code;
}

void CodeGenerator::makeAnd(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode) {

    int labelNumValue = this->getLabel();
    CodeOperand labelTrue = {.operandType=label, .numericalValue= labelNumValue};
    CodeOperand labelFalse = {.operandType=patchworkFalse, .numericalValue=-1};

    symbolNode->hasPatchworks = true;
    

    //se tem remendos, é uma expressão booleana. Remenda
    if (leftOperandNode->hasPatchworks) {
        
        this->coverPatchworks(leftOperandNode, labelTrue, true);
        this->appendCode(symbolNode,leftOperandNode);
        
    } 
    // se não, compara
    else {
        this->appendCode(symbolNode,leftOperandNode);
        CodeOperand r1Operand = leftOperandNode->resultRegister;
        list<InstructionCode> compareCode = makeCompare(r1Operand, labelTrue, labelFalse);
        this->coverPatchworks(compareCode, labelTrue, true);
        appendCode(symbolNode, compareCode);
    }

    symbolNode->code.push_back(this->makeNop(labelNumValue));
    this->appendCode(symbolNode, rightOperandNode);

    if (!rightOperandNode->hasPatchworks) {
        CodeOperand r1Operand = rightOperandNode->resultRegister;
        list<InstructionCode> compareCode = makeCompare(r1Operand, {.operandType=patchworkTrue, .numericalValue=-1}, labelFalse);
        appendCode(symbolNode, compareCode);
    }
    
    cout << "----------" << endl;
    cout << "----------" << endl;
    codePrinter.printTree((void *)symbolNode);
    cout << "----------" << endl;
    cout << "----------" << endl;
   

}

//EX.: add r1, r2 => r3
InstructionCode CodeGenerator::makeBinaryInstruction(InstructionType instructionType, int prefixLabel, CodeOperand r1Operand, CodeOperand r2Operand, CodeOperand r3Operand) {

    list<CodeOperand> leftList; 
    list<CodeOperand> rightList; 

    leftList.push_back(r1Operand);
    leftList.push_back(r2Operand);
    rightList.push_back(r3Operand);

    InstructionCode code = {
        .prefixLabel =prefixLabel,
    .instructionType=instructionType, 
    .leftOperands= leftList, 
    .rightOperands= rightList};

    return code;

}

//Ex.: add r1, r2 => r3
void CodeGenerator::makeBinaryOperation(AST *leftOperandNode, AST *symbolNode, AST *rightOperandNode) {

    list<InstructionCode> codeList;
    int r3 = this->getRegister();
    int addLabel;
    CodeOperand r3Operand = {.operandType=_register, .numericalValue=r3};
    CodeOperand r1Operand;
    CodeOperand r2Operand;

    if (!leftOperandNode->hasPatchworks && !rightOperandNode->hasPatchworks) {
        addLabel = -1;
    }else {
        addLabel = this->getLabel();
    }

    if (leftOperandNode->hasPatchworks) {
        int r1 = this->getRegister();
        r1Operand = {.operandType=_register, .numericalValue=r1};
        list<InstructionCode> newCode = this->createBoolFlow(leftOperandNode, addLabel, r1Operand);
        codeList.insert(codeList.end(), leftOperandNode->code.begin(), leftOperandNode->code.end());
        codeList.insert(codeList.end(), newCode.begin(), newCode.end());
    
    } else {
        r1Operand = leftOperandNode->resultRegister;
        codeList.insert(codeList.end(), leftOperandNode->code.begin(), leftOperandNode->code.end());
    }

    if (rightOperandNode->hasPatchworks) {
        int r2 = this->getRegister();
        r2Operand = {.operandType=_register, .numericalValue=r2};
        list<InstructionCode> newCode = this->createBoolFlow(rightOperandNode, addLabel, r2Operand);
        codeList.insert(codeList.end(), rightOperandNode->code.begin(), rightOperandNode->code.end());
        codeList.insert(codeList.end(), newCode.begin(), newCode.end());
    
    } else {
        r2Operand = rightOperandNode->resultRegister;
        codeList.insert(codeList.end(), rightOperandNode->code.begin(), rightOperandNode->code.end());
    }

    InstructionCode addCode = this->makeBinaryInstruction(symbolNode->nodeInstructionType, addLabel, r1Operand, r2Operand, r3Operand);
    codeList.push_back(addCode);
    symbolNode->code = codeList;
    symbolNode->resultRegister = r3Operand;
    symbolNode->hasPatchworks = false;

}

void CodeGenerator::appendCode(AST *parent, AST*child) {

    if (parent == NULL || child ==  NULL) { return; }

    parent->code.insert(parent->code.end(), child->code.begin(), child->code.end());

}

void CodeGenerator::appendCode(AST *parent, list<InstructionCode> newCode) {

    if (parent == NULL) { return; }

    parent->code.insert(parent->code.end(), newCode.begin(), newCode.end());

    
}
