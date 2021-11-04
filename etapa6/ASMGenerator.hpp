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
    void generateAttribution(InstructionCode code);
    void generateReturn();
    void generateASMNormalCode(InstructionCode code);
    void generateBinaryOperation(InstructionCode code);
    string binaryOperationCorrespondent(InstructionCode code);

public: 
    ASMGenerator();
    void generateAsm(SymbolTable globalScope, list<InstructionCode> code);

};