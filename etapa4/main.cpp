/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include <stdio.h>

void *arvore = NULL;

extern "C"
{
  void exporta (void *arvore);
  void libera (void *arvore);
  int yyparse(void);
	int yylex(void);  
  int yylex_destroy(void);
 
}

int main (int argc, char **argv)
{
  int ret = yyparse();
  exporta (arvore);
  libera(arvore);
  arvore = NULL;
  yylex_destroy();
  return ret;
}
