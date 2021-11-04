/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "ASMGenerator.hpp"
#include "SymbolTable.hpp"
#include "Code.hpp"
#include "AST.hpp"
#include <list>
#include <iostream>

using namespace std;

ASMGenerator::ASMGenerator() { }

// Example:
//  .comm   variableName,4
void ASMGenerator::generateGlobalVariable(string variableName) {
    cout << "\t" << ".comm" << "\t";
    cout << variableName;
    cout << ",4";
    cout << endl;
}

// Example:
//  .globl	functionName
//  .type   functionName, @function
void ASMGenerator::generateFunctionDeclaration(string functionName) {
    cout << "\t" << ".globl" << "\t";
    cout << functionName;
    cout << endl;
    
    cout << "\t" << ".type" << "\t";
    cout << functionName;
    cout << ", @function";
    cout << endl;
}


//  .file   "etapa6.c"
//  .text
void ASMGenerator::generateInitialLines() {
    cout << "\t" << ".file" << "\t";
    cout << "\"etatpa6.c\"";
    cout << endl;

    cout << "\t" << ".text";
    cout << endl;
}

void ASMGenerator::generateDataSegment(SymbolTable globalScope) {

    for (auto it : globalScope.getTableVariables()) {
        string key = it.first;
        SymbolTableValue value = it.second;

        switch (value.kind)
        {
        case variableKind:
            this->generateGlobalVariable(key);
            break;
        
        case functionKind:
            this->generateFunctionDeclaration(key);
            break;
        default:
            break;
        } 
        
    }
}

// function name:
// label:
void ASMGenerator::generateFunctionBegin(InstructionCode code) {

    cout << "L" << code.prefixLabel << ":";
    cout << endl;
    cout << code.details.name << ":";
    cout << endl;

}

void ASMGenerator::generateReturn() {

    cout << "\t" << "ret";

}

string ASMGenerator::binaryOperationCorrespondent(InstructionCode code) {

    switch (code.instructionType)
    {
        case add:
            return "add";
        case mult:
            return "mull";
        case _div: 
            return "divl";
        case sub:
            return "subl";
        default:
            return "";
    }

}

// Example
//  addl %edx, %eax
void ASMGenerator::generateBinaryOperation(InstructionCode code) {

    cout << "\t";
    cout << binaryOperationCorrespondent(code);
    cout << "\t";
    cout << "%edx";
    cout << ", ";
    cout << "%eax";
    cout << endl;

}

// Locais
// storeAI r0 => rfp, 8 ----> movl    %eax, -8(%rbp)
// Globais
// storeAI r0 => rbss, 8 ----> movl    %eax, variableName(%rip)
void ASMGenerator::generateAttribution(InstructionCode code) {

    cout << "\t" << "movl" << "\t";

    // left operators
    cout << "%eax";
    
    cout << ", ";

    // right operators
    // global
    if (code.rightOperands.front().numericalValue == rbss) {
        cout << code.details.name;
        cout << "(" << "%rip" << ")";
       
    } 
    // local
    else {
        int number = code.rightOperands.back().numericalValue;
        cout << "-" << number;
        cout << "(" << "%rbp" << ")";
    }

    cout << endl;

} 

// Generates ASM for InstructionCode with details
void ASMGenerator::generateASMSpecialCode(InstructionCode code) {

    switch (code.details.nodeType)
    {
    case functionType:
        generateFunctionBegin(code);
        break;

    case attributionType:
        generateAttribution(code);
        break;
    
    default:
        break;
    }

}

// 1 to 1 instructions
void ASMGenerator::generateASMNormalCode(InstructionCode code) {

    switch(code.instructionType) {
        
        case _div:
        case mult:
        case add:
        case sub:
            generateBinaryOperation(code);
            break;

        default:
        break;
    }
}

void ASMGenerator::generateCodeSegment(list<InstructionCode> code) {

    list<InstructionCode>::iterator it;
    for (it = code.begin(); it != code.end(); ++it) {

        if (it->details.notEmpty) {
            generateASMSpecialCode(*it);
        } else {
            generateASMNormalCode(*it);
        }

    }
    
} 

void ASMGenerator::generateAsm(SymbolTable globalScope, list<InstructionCode> code) {
    this->generateInitialLines();
    this->generateDataSegment(globalScope);
    this->generateCodeSegment(code);
}