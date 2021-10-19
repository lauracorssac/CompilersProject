/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include <stdio.h>
#include <list>
#include <iostream>
#include "SymbolTableStack.hpp"
#include "SyntacticalType.hpp"
#include "ReleaseManager.hpp"
extern "C"
{
 
  int yyparse(void);
	int yylex(void);  
  int yylex_destroy(void);
 
}

void *arvore = NULL;
ReleaseManager releaseManager;
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
    // cout << "loadI 1024 => rfp" << endl;
    // cout << "loadI 1024 => rsp" << endl;
    // cout << "loadI 7 => rbss" << endl;
    // cout << "jumpI => L0" << endl;
    // cout << "L0: addI rsp, 0 => rsp" << endl;
    // cout << "halt" << endl;
  releaseManager.freeReleasePool();
  arvore = NULL;
  tableStack.endAllScopes();
  yylex_destroy();
}

