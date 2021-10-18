/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "CodeGenerator.hpp"
#include "Utils.hpp"
#include <string>

extern "C" {
    #include "AST.h"
}

using namespace std;

CodeGenerator::CodeGenerator() { 
    this->registerNumber = 0;
}

string CodeGenerator::generateRegister() {
    
    // increment registerNumber after use
    return "r" + to_string(this->registerNumber++);
}

string CodeGenerator::makeLiteralCode(AST *literalNode) {

    string nodeValue = stringFromLiteralValue(literalNode->value->literalTokenValueAndType);
    string finalString = "loadI " + nodeValue + "=> " + this->generateRegister() + "\n";
    copyStringToCharPointer(finalString, literalNode->code->codeString);
}

