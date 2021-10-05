/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include <stdio.h>
#include "SymbolTableStack.hpp"

extern "C"
{
  #include "SyntacticalType.h"
  void exporta (void *arvore);
  void libera (void *arvore);
  int yyparse(void);
	int yylex(void);  
  int yylex_destroy(void);
 
}

void *arvore = NULL;
SymbolTableStack tableStack;

int main (int argc, char **argv)
{
  int ret = yyparse();
  tableStack.printItself();
  exporta (arvore);
  libera(arvore);
  arvore = NULL;
  yylex_destroy();
  return ret;
}
