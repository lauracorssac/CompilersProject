/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include <stdio.h>
#include <list>
#include <iostream>
#include "SymbolTableStack.hpp"


extern "C"
{
  #include "SyntacticalType.h"
  #include "ReleaseManager.h"
  void exporta (void *arvore);
  void libera (void *arvore);
  void insertNewNode(AST *newNode);
  int yyparse(void);
	int yylex(void);  
  int yylex_destroy(void);
 
}

void *arvore = NULL;
SymbolTableStack tableStack;
void executeShutDownRoutine();
using namespace std;

int main (int argc, char **argv)
{
  int ret = yyparse();
  executeShutDownRoutine();
  return ret;
}

void executeShutDownRoutine() {
  exporta (arvore);
  freeReleasePool();
  arvore = NULL;
  tableStack.endAllScopes();
  yylex_destroy();
}

