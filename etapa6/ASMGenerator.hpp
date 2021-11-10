/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTable.hpp"
#include "Code.hpp"
#include <list>
#include <string>

using namespace std;

class ASMGenerator {

private:
    int quantityOfParametersNextCall;
    int labelNumber;
    int getLabel();

    void generateDataSegment(SymbolTable globalScope);
    void generateGlobalVariable(string variableName);
    void generateInitialLines();
    void generateFunctionDeclaration(string functionName);
    void generateCodeSegment(list<InstructionCode> code);
    void generateFunctionBegin(InstructionCode code);
    void generateASMSpecialCode(InstructionCode code);
    void generateStoreAI(InstructionCode code);
    void generateReturn();
    void generateASMNormalCode(InstructionCode code);
    void generateBinaryOperation(InstructionCode code);
    void generateDivisionOperation(InstructionCode code);
    void generateUnaryMinus(InstructionCode code);
    string binaryOperationCorrespondent(InstructionCode code);
    void generateLoadAI(InstructionCode code);
    void pushValue();
    void popValue(string destinationRegister);
    string registerAuxCorrespondent(list<CodeOperand> operands, InstructionAdditionalDetails details);
    void generateLoadI(InstructionCode code);
    void pushNumber(int number);
    void generatei2i(InstructionCode code);
    void generateJumpI(InstructionCode code);
    string registerAuxCorrespondent(CodeOperand operand);
    void verifyPrefixLabel(InstructionCode code);
    void generateNop(int labelNumber);
    void generateAddI(InstructionCode code);
    void generateSubI(InstructionCode code);
    void generateHalt();
    void generateFunctionCall(string functionName);
    void generateFunctionReturn();
    void generateFunctionPrologue(InstructionCode code);
    void generatePushRBP();
    void movRBPToRSP();
    void movRSPToRBP();
    void generatePopRBP();
    void generateIncrementRSP(InstructionCode code);
    void popReturnValue();
    void pushReturnValue();
    void makeParameterCopy(int quantityOfParameters);
    void generateCBR(InstructionCode code);
    void generateCompare(InstructionCode code, bool inverted=false);
    void pushComparissonResult(InstructionCode code);
    
public: 
    ASMGenerator();
    void generateAsm(SymbolTable globalScope, list<InstructionCode> code);

};