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
    string binaryOperationCorrespondent(InstructionCode code);
    void generateLoadAI(InstructionCode code);
    void pushValue();
    void popValue(string destinationRegister);
    string registerAuxCorrespondent(list<CodeOperand> operands, InstructionAdditionalDetails details);
public: 
    ASMGenerator();
    void generateAsm(SymbolTable globalScope, list<InstructionCode> code);

};