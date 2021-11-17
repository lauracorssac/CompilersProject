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

ASMGenerator::ASMGenerator() {
    this->labelNumber = 0;
    quantityOfParametersNextCall = 0;
}

int ASMGenerator::getLabel() {
    
    // increment labelNumber after use
    return this->labelNumber++;
}

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

    // cout << "L" << code.prefixLabel << ":";
    // cout << endl;
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
            return "addl";
        case mult:
            return "imull";
        case _div: 
            return "idivl";
        case sub:
            return "subl";
        case cmp_EQ:
            return "je";
        case cmp_GE:
            return "jge";
        case cmp_LE:
            return "jle";
        case cmp_NE:
            return "jne";
        case cmp_GT:
            return "jg";
        case cmp_LT:
            return "jl";
        default:
            return "";
    }

}

// Pushes whatever is stored in %eax into stack
void ASMGenerator::pushValue() {

    cout << "# push" << endl;
    cout << "\t" << "subq" << "\t";
    cout << "$4" << ", " << "%rsp";
    cout << endl;

    cout << "\t" << "movl" << "\t";
    cout << "%eax";
    cout << ", " << "(%rsp)";
    cout << endl;

}

// Pushes a numerical literal into stack
void ASMGenerator::pushNumber(int number) {
    
    cout << "# push" << endl;
    cout << "\t" << "subq" << "\t";
    cout << "$4" << ", " << "%rsp";
    cout << endl;

    cout << "\t" << "movl" << "\t";
    cout << "$" << number;
    cout << ", " << "(%rsp)";
    cout << endl;

}

// Example
// From:    jumpI => L1
// To:      jmp L1
void ASMGenerator::generateJumpI(InstructionCode code) {

    cout << "\t" << "jmp" << "\t";
    cout <<  "L" << code.rightOperands.front().numericalValue;
    cout << endl;

}

string ASMGenerator::registerAuxCorrespondent(CodeOperand operand) { 

    if (operand.numericalValue == rsp) {
        return "%rsp";
    } 

    if (operand.numericalValue == rfp) {
        return "%rbp";
    }

    return "";
}
// Example 0
// From:    addI rsp, 4 => rsp
// To:      subq	$4, %rsp
// Example 1
// From:    addI rpc, 5 => r1
// To:      movq	%rip, %eax + subq $5, %eax + push

void ASMGenerator::generateAddI(InstructionCode code) {

    if (code.leftOperands.front().numericalValue == rsp) {
        cout << "\t" << "subq" << "\t";
        cout << "$" << code.leftOperands.back().numericalValue;
        cout << ", ";
        cout << "%rsp";
        cout << endl;
    } else if(code.leftOperands.front().numericalValue == rpc) {
        //movq	%rip, %eax
        // cout << "\t" << "movq" << "\t";
        // cout << "%eip";
        // cout << ", ";
        // cout << "%rax";
        // cout << endl;

        cout << "\t"<< "leaq" << "\t";
        cout << "0(%rip)";
        cout << ", ";
        cout << "%rax";
        cout << endl;

        //subl $5, %eax
        cout << "\t" << "subq" << "\t";
        cout << "$" << code.leftOperands.back().numericalValue;
        cout << ", ";
        cout << "%rax";
        cout << endl;

        cout << "\t" << "pushq" << "\t" << "%rax";
        cout << endl;
        //pushValue();
    }

}

// Example
// From:    subI rsp, 4 => rsp
// To:      addq $4, %rsp
void ASMGenerator::generateSubI(InstructionCode code) {

    if (code.leftOperands.front().numericalValue == rsp) {
        cout << "\t" << "addq" << "\t";
        cout << "$" << code.leftOperands.back().numericalValue;
        cout << ", ";
        cout << "%rsp";
        cout << endl;
    }
}

void ASMGenerator::popValue(string destinationRegister) {

    cout << "# pop" << endl;
    cout << "\t" << "movl" << "\t";
    cout << "(" << "%rsp" << ")";
    cout << ", " << destinationRegister;
    cout << endl;

    cout << "\t" << "addq" << "\t";
    cout << "$4" << ", " << "%rsp";
    cout << endl;

}

string ASMGenerator::registerAuxCorrespondent(list<CodeOperand> operands, InstructionAdditionalDetails details) {

    if (operands.front().numericalValue == rbss) {
        return details.name + "(" + "%rip" + ")";
       
    } 
    // local
    else {
        string number = to_string(details.offset + 4);
        return "-" + number + "(" + "%rbp" + ")";
    }

}


// From:    loadAI rfp, 12 => r1  
// To:      movl    -12(%rbp), %eax
// + push instruction
void ASMGenerator::generateLoadAI(InstructionCode code) {

    cout << "\t" << "movl" << "\t";
    
    cout << this->registerAuxCorrespondent(code.leftOperands, code.details);

    cout << ", %eax";
    cout << endl;

    pushValue();

}

void ASMGenerator::verifyPrefixLabel(InstructionCode code) {
    if (code.prefixLabel != -1) {
        generateNop(code.prefixLabel);
    }
}

void ASMGenerator::generateNop(int labelNumber) {
    cout << "L" << labelNumber << ":";
    cout << endl;
}

// From:    loadI 0 => r0
// To:      push 0 instruction
void ASMGenerator::generateLoadI(InstructionCode code) {

    cout << "# load I" << endl;
    if (code.rightOperands.front().operandType == registerPointer) {

        cout <<  "\t" << "movl" << "\t";
        cout <<  "$" << code.leftOperands.front().numericalValue;
        cout << ", ";
        cout << "(" << registerAuxCorrespondent(code.rightOperands.front()) << ")";
        cout << endl;

    } else {
        this->pushNumber(code.leftOperands.front().numericalValue);
    }

}

// Example
// addl %edx, %eax
// result will be on %eax
// does %eax op %edx
void ASMGenerator::generateBinaryOperation(InstructionCode code) {

    popValue("%edx");
    popValue("%eax");

    cout << "\t";
    cout << binaryOperationCorrespondent(code);
    cout << "\t";
    cout << "%edx";
    cout << ", ";
    cout << "%eax";
    cout << endl;

    pushValue();

}

// Example
//  addl %edx, %eax
void ASMGenerator::generateDivisionOperation(InstructionCode code) {

    //divisor
    popValue("%ecx");
    //dividend
    popValue("%eax");
    
    // expands dividend
    cout << "\t" << "cltd";
    cout << endl;

    // divides dividend by divisor
    cout << "\t";
    cout << binaryOperationCorrespondent(code);
    cout << "\t";
    cout << "%ecx";
    cout << endl;
    
    //result in dividend %eax
    pushValue();

}


// Local
// storeAI r0 => rfp, 8 ----> movl    %eax, -8(%rbp)
// Global
// storeAI r0 => rbss, 8 ----> movl    %eax, variableName(%rip)
void ASMGenerator::generateStoreAI(InstructionCode code) {

    popValue("%eax");

    cout << "\t" << "movl" << "\t";

    cout << "%eax";
    
    cout << ", ";

    cout << registerAuxCorrespondent(code.rightOperands, code.details);

    cout << endl;

} 

//movq	%rsp, %rbp
void ASMGenerator::movRSPToRBP() {
    cout << "\t" << "movq" << "\t";
    cout << "%rsp";
    cout << ", ";
    cout << "%rbp";
    cout << endl;
}

//Mov rbp, rsp
void ASMGenerator::movRBPToRSP() {
    cout << "\t" << "movq" << "\t";
    cout << "%rbp";
    cout << ", ";
    cout << "%rsp";
    cout << endl;
}

//popq %rbp
void ASMGenerator::generatePopRBP() {
    cout << "\t" << "popq" << "\t";
    cout << "%rbp";
    cout << endl;
}

//pushq %rbp
void ASMGenerator::generatePushRBP() {
    cout << "\t" << "pushq" << "\t";
    cout << "%rbp";
    cout << endl;
}

void ASMGenerator::makeParameterCopy(int quantityOfParameters) {

    int i=0;
    int offsetParameter; // in relation to rbp
    int indexOfParameter; // From quant to 1
    int offsetLocalVar; // From -4 to -4*quant

    while ( i < quantityOfParameters) {

        cout << "# mov parameter" << endl;
        indexOfParameter = quantityOfParameters - i - 1;
        
        // 16 = size(rbp) + size(ret add)
        // last pushed param is 16 bytes from rbp
        offsetParameter = 4 * indexOfParameter + 16; 
        offsetLocalVar = -4 * (i+1);

        cout << "\t" << "movl" << "\t";
        cout << offsetParameter << "(%rbp)";
        cout << ", ";
        cout << "%eax";
        cout << endl;

        cout << "\t" << "movl" << "\t";
        cout << "%eax";
        cout << ", ";
        cout << offsetLocalVar << "(%rbp)";
        cout << endl;
       
        i++;
    }

}

void ASMGenerator::generateFunctionPrologue(InstructionCode code) {

    generateFunctionBegin(code);
    generatePushRBP();
    movRSPToRBP();

}

void ASMGenerator::generateFunctionReturn() {

    movRBPToRSP();
    generatePopRBP();
    cout << "\t" << "ret" << "\t";
    cout << endl;
    
}

//call	d
void ASMGenerator::generateFunctionCall(string functionName) {
    
    if (functionName == "main") { return; }

    cout << "\t" << "call" << "\t";
    cout << functionName;
    cout << endl;
}

// From:    addI rsp, x => rsp 
// To:      subq y, %rsp
void ASMGenerator::generateIncrementRSP(InstructionCode code) {

    cout << "\t" << "subq" << "\t";
    cout << "$" << code.details.offset;
    cout << ", ";
    cout << "%rsp";
    cout << endl;

}

void ASMGenerator::popReturnValue() {
    popValue("%eax");
}
void ASMGenerator::pushReturnValue() {
    cout << "# push return value" << endl;
    pushValue();
}

void ASMGenerator::popParameters(int quantityOfParameters) {
    cout << "# pop " << quantityOfParameters << " parameters"  << endl;
    int i =0;
    while (i < quantityOfParameters) {
        popValue("%edx");
        i+=1;
    }
 
}

// From: cmp_NE r1, r2 => r3
// To:   cmp %edx, %eax
void ASMGenerator::generateCompare(InstructionCode code, bool inverted) {

    cout << "# compare" << endl;
    popValue(inverted ? "%edx" : "%eax");
    popValue(inverted ? "%eax" : "%edx");

    cout << "\t" << "cmpl" << "\t";
    cout << "%edx";
    cout << ", ";
    cout << "%eax";
    cout << endl;

}

// From: cbr r3 => labelT, labelF
// To:   JE labelF
//      JMP labelT
void ASMGenerator::generateCBR(InstructionCode code) {

    cout << "# CBR" << endl;
    cout << "\t" << "je" << "\t";
    cout << "L" << code.rightOperands.back().numericalValue;
    cout << endl;

    cout << "\t" << "jmp" << "\t";
    cout << "L" << code.rightOperands.front().numericalValue;
    cout << endl;

}

// Generates ASM for InstructionCode with details
void ASMGenerator::generateASMSpecialCode(InstructionCode code) {

    switch (code.details.instructionCodeType)
    {

     //instructions for return rp = return procedure  
    case rpStoreReturnValueType:
        popReturnValue();
        break;
    case rpLoadReturnValueType:
        generateLoadI(code);
        break;
    case rpLoadReturnAddressType:
    case rpLoadRSPType:
    case rploadRFPType:
    case rpStoreRSPType:
    case rpStoreRFPType:
        break;
    case rpJumpReturnAddressType:
        generateFunctionReturn();
        break;

    //instructions for call cp = call procedure
    case cpStoreRegisterType:
    case cpIncrementRSPType:
    case cpDecrementRSPType:
    case cpIncrementRPCType:
    case cpStoreRPCType:
    case cpStoreRSPType:
    case cpStoreRFPType:
        break;
    case cpStoreParameterType:
        break;
    case cpLoadReturnValueType:
        pushReturnValue();
        break;
    case cpJumpFunctionType:
        generateFunctionCall(code.details.name);
        //offser here contains the 
        popParameters(code.details.offset);
        break;

    //instructions for function prologue fp = function procedure
    case fpFunctionNopType:
        // offset here contains quantity of parameters
        quantityOfParametersNextCall = code.details.offset;
        generateFunctionPrologue(code);
        break;    
    case fpi2iRSPRFP:
    case fpLoadParameterType:
    case fpStoreParameterType:
        break;

    case attributionStoreType:
        generateStoreAI(code);
        break;
    
    case loadIdentifierType:
        generateLoadAI(code);
        break;

    case fpIncrementLocalVariableOffsetRSPType:
        generateIncrementRSP(code);
        makeParameterCopy(quantityOfParametersNextCall);
        break;
    
    case bfCompareNE:
        generateCompare(code);
        break;
    default:
        break;
    }

}

void ASMGenerator::pushComparissonResult(InstructionCode code) {

    int labelTrue = getLabel();
    int labelEnd = getLabel();

    cout << "\t" << binaryOperationCorrespondent(code) << "\t";
    cout << "AL" << labelTrue;
    cout << endl;
    
    pushNumber(0);
    cout << "\t" << "jmp" << "\t";
    cout << "AL" << labelEnd;
    cout << endl;
    
    cout << "AL" << labelTrue << ":" << endl;
    pushNumber(1);

    cout << "AL" << labelEnd << ":" << endl;

}

void ASMGenerator::generateUnaryMinus(InstructionCode code) {

    popValue("%eax");
    cout << "\t" << "negl" << "\t";
    cout << "%eax";
    cout << endl;

    pushValue();

}

// 1 to 1 instructions
void ASMGenerator::generateASMNormalCode(InstructionCode code) {

    switch(code.instructionType) {

        case _div:
            generateDivisionOperation(code);
            break;
        case mult:
        case add:
        case sub:
            generateBinaryOperation(code);
            break;
        case rsubI:
            generateUnaryMinus(code);
            break;
        case cmp_EQ:
        case cmp_NE:
        case cmp_GE:
        case cmp_LE:
        case cmp_GT:
        case cmp_LT:
            generateCompare(code, true);
            pushComparissonResult(code);
            break;
        
        case loadI:
            generateLoadI(code);
            break;
        case jumpI:
            generateJumpI(code);
            break;
        case addI:
            generateAddI(code);
            break;
        case subI:
            generateSubI(code);
            break;
        case cbr:
            generateCBR(code);
            break;
        
        default:
        break;
    }
}



void ASMGenerator::generateCodeSegment(list<InstructionCode> code) {

    list<InstructionCode>::iterator it;
    for (it = code.begin(); it != code.end(); ++it) {
        //cout << "# inst" << it->instructionType << endl;

        verifyPrefixLabel(*it);

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