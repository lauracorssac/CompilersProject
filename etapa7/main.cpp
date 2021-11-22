/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include <stdio.h>
#include <list>
#include <iostream>
#include <string.h>
#include "SymbolTableStack.hpp"
#include "SyntacticalType.hpp"
#include "ReleaseManager.hpp"
#include "CodeGenerator.hpp"
#include "CodePrinter.hpp"
#include "ASMGenerator.hpp"

extern "C"
{
 
  int yyparse(void);
	int yylex(void);  
  int yylex_destroy(void);
 
}

void *arvore = NULL;
ReleaseManager releaseManager;
SymbolTableStack tableStack;
CodePrinter codePrinter;
CodeGenerator codeGenerator;
ASMGenerator asmGenerator;
void executeShutDownRoutine();
int parseInput(int argc, char *argv[]);
using namespace std;
bool optimized;


int main (int argc, char *argv[])
{

  optimized = parseInput(argc, argv);
  tableStack.beginNewScope();
  int ret = yyparse();
  executeShutDownRoutine();
  return ret;
}

int parseInput(int argc, char *argv[]) {
  if (argc == 2) {
    string argString(argv[1]);
    if (argString.size() == 2) {
        char lastChar = argString[1];
        lastChar = tolower(lastChar);
        return lastChar == 'o';
    }

  } 
  return false;
}

void executeShutDownRoutine() {

  AST *tree = (AST*)arvore;
  if (tree != NULL) {
    codeGenerator.generateFinalCode(tree);
    codeGenerator.generateInitialCode(tree);
    //codePrinter.printTree(arvore);
  }
  
  asmGenerator.generateAsm(tableStack.getLastScope(), tree->code);
  
  //exporta (arvore);
  releaseManager.freeReleasePool();
  arvore = NULL;
  tableStack.endAllScopes();
  yylex_destroy();
}

