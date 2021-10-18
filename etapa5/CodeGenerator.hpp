/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

using namespace std;
#include <string>

class CodeGenerator
{
private:
    int registerNumber;
    string generateRegister();
public:
    CodeGenerator();
    string CodeGenerator::makeLiteralCode(AST *literalNode);



};





#endif