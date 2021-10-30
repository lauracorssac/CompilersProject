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

  if (arvore != NULL) {
    codeGenerator.generateFinalCode((AST*)arvore);
    codeGenerator.generateInitialCode((AST*)arvore);
    codePrinter.printTree(arvore);
  }
  
  //exporta (arvore);
  releaseManager.freeReleasePool();
  arvore = NULL;
  tableStack.endAllScopes();
  yylex_destroy();
}

