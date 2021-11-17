/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include <stdio.h>
#include <list>
#include <iostream>
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
using namespace std;


int main (int argc, char **argv)
{
  tableStack.beginNewScope();
  int ret = yyparse();
  executeShutDownRoutine();
  return ret;
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

