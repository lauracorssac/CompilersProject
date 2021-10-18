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
  //exporta (arvore);
    cout << "loadI 1024 => rfp" << endl;
    cout << "loadI 1024 => rsp" << endl;
    cout << "loadI 7 => rbss" << endl;
    cout << "jumpI => L0" << endl;
    cout << "L0: addI rsp, 0 => rsp" << endl;
    cout << "halt" << endl;
  freeReleasePool();
  arvore = NULL;
  tableStack.endAllScopes();
  yylex_destroy();
}

