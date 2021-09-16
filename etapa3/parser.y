%{
#include "LexicalValue.h"
#include <stdio.h>
#include "AST.h"

#define YYDEBUG 1
int yylex(void);
int yyerror (char const *s);
extern int get_line_number(void);
extern void *arvore;
%}

%union {
	struct LexicalValue *lexicalValue;
	struct AST *node;
}

%start programa

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_PR_END
%token TK_PR_DEFAULT
%token<lexicalValue> TK_OC_LE
%token<lexicalValue> TK_OC_GE
%token<lexicalValue> TK_OC_EQ
%token<lexicalValue> TK_OC_NE
%token<lexicalValue> TK_OC_AND
%token<lexicalValue> TK_OC_OR
%token<lexicalValue> TK_OC_SL
%token<lexicalValue> TK_OC_SR
%token<lexicalValue> TK_LIT_INT
%token<lexicalValue> TK_LIT_FLOAT
%token<lexicalValue> TK_LIT_FALSE
%token<lexicalValue> TK_LIT_TRUE
%token<lexicalValue> TK_LIT_CHAR
%token<lexicalValue> TK_LIT_STRING
%token<lexicalValue> TK_IDENTIFICADOR
%token TOKEN_ERRO

%type<node> att
%type<node> A2 

%type<node> literal
%type<node> literalNum
%type<node> literalBool

%type<node> operando
%type<node> expressao
%type<node> E0
%type<node> E1
%type<node> E2
%type<node> E3
%type<node> E4
%type<node> E5
%type<node> E6
%type<node> E7
%type<node> E8
%type<node> E9
%type<node> E10

%type<node> bloco
%type<node> B1
%type<node> simples
%type<node> local
%type<node> io
%type<node> shift
%type<node> rbc
%type<node> if
%type<node> while
%type<node> for
%type<node> chamada

%type<node> funcao
%type<node> F1
%type<node> F2
%type<node> F3
%type<node> F4
%type<node> F5
%type<node> F6
%type<node> F7

%type<node> L1
%type<node> L2
%type<node> L3
%type<node> L4
%type<node> L5
%type<node> L6

%type<node> entrada
%type<node> saida

%type<node> programa


%%
tipo : TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL | TK_PR_CHAR | TK_PR_STRING;

literal: TK_LIT_INT { $$ = createNode($1); }
| TK_LIT_FLOAT { $$ = createNode($1); }
| TK_LIT_FALSE { $$ = createNode($1); }
| TK_LIT_TRUE { $$ = createNode($1); }
| TK_LIT_CHAR { $$ = createNode($1); }
| TK_LIT_STRING { $$ = createNode($1); };

literalNum: TK_LIT_INT { $$ = createNode($1); }
| TK_LIT_FLOAT { $$ = createNode($1); };
literalBool: TK_LIT_TRUE { $$ = createNode($1); }
| TK_LIT_FALSE { $$ = createNode($1); };

simples: bloco ';' { $$ = $1; }
| local { $$ = $1; }
| att ';' { $$ = $1; }
| io { $$ = $1; }
| shift { $$ = NULL; }
| rbc { $$ = $1; }
| if ';' { $$ = NULL; }
| while ';' { $$ = NULL; }
| for ';' { $$ = NULL; }
| chamada ';' { $$ = NULL; }; 

indexador: '[' TK_LIT_INT ']';

operando: literalNum { $$ = $1; }
| TK_IDENTIFICADOR { $$ = createNode($1); }
| TK_IDENTIFICADOR '[' expressao ']' { $$ = NULL; } 
| chamada { $$ = NULL; }
| literalBool { $$ = $1; }; 

opShift: TK_OC_SL | TK_OC_SR;

 /*    def operadores binarios    
	
	ordem decrescente de precedencia
	opNivelX: quanto menor o X, maior a precedencia do operador
 */
opNivel1: '^';
opNivel2: '*' | '/' | '%';
opNivel3: '+' | '-';

 /* relacionais */
opNivel4: TK_OC_LE | TK_OC_GE | '<' | '>';

/* equalidade */
opNivel5: TK_OC_EQ | TK_OC_NE;

 /* bitwise and */
opNivel6: '&'; 

/* bitwise or */
opNivel7: '|';

 /* logical and */ 
opNivel8: TK_OC_AND;

 /* logical or */
opNivel9: TK_OC_OR;

 /* operadores unarios */
unarios: '-' | '+' | '*' | '&' | '#' | '!' | '?';

 /*    def expressao    
	
	inicial: expressao
	final: E10

 */

expressao: E0 { $$ = $1; }
| expressao '?' E0 ':' E0 { $$ = NULL; };
E0: E1 { $$ = $1; }
| E0 opNivel9 E1 { $$ = NULL; };
E1: E2 { $$ = $1; }
| E1 opNivel8 E2 { $$ = NULL; };
E2: E3 { $$ = $1; }
| E2 opNivel7 E3 { $$ = NULL; };
E3: E4 { $$ = $1; }
| E3 opNivel6 E4 { $$ = NULL; };
E4: E5 { $$ = $1; }
| E4 opNivel5 E5 { $$ = NULL; };
E5: E6 { $$ = $1; }
| E5 opNivel4 E6 { $$ = NULL; };
E6: E7 { $$ = $1; }
| E6 opNivel3 E7 { $$ = NULL; };
E7: E8 { $$ = $1; }
| E7 opNivel2 E8 { $$ = NULL; };
E8: E9 { $$ = $1; }
| E8 opNivel1 E9 { $$ = NULL; };
E9: E10 { $$ = $1; }
| unarios E10 { $$ = NULL; };
E10: operando { $$ = $1; }
| '(' expressao ')' { $$ = NULL; };

programa : programa global { $$ = $1; }
| programa funcao { 
	if ($1 == NULL) {
		arvore = (void*)$2;
		$$ = $2;
	} else {
		appendChild($1, $2);
	}
	$$ = $2;
}
| { $$ = NULL };


 /*    def var global    
	
	inicial: global
	terminais: C D

 */
global: TK_PR_STATIC A | A;
A : tipo B;
B : TK_IDENTIFICADOR C;
 /*    terminais da global    */
C : ';' | ',' B | indexador D;
D : ';' | ',' B;


 /*    def funcao    
	
	inicial: funcao
	terminais: F6 F4

  */
funcao: TK_PR_STATIC F1 { $$ = $2; }
| F1 { $$ = $1; };
F1: tipo F2 { $$ = $2; };
F2: TK_IDENTIFICADOR F3 { 
	AST *rootNode = createNode($1);
	appendChild(rootNode, $2);
	$$ = rootNode;
};
F3: '(' F4 { $$ = $2; };
F4: ')' bloco { $$ = $2; }
| tipo F5 { $$ = $2; }
| TK_PR_CONST tipo F5 { $$ = $3; };
F5: TK_IDENTIFICADOR F6 { $$ = $2; };
F6: ')' bloco {  $$ = $2; }
| ',' F7  { $$ = $2; };
F7: tipo F5 { $$ = $2; }
| TK_PR_CONST tipo F5 { $$ = $3; };

 /*    def bloco    
	
	inicial: bloco
	terminais: B1

 */

bloco: '{' B1 { $$ = $2;};
B1: '}' { $$ = NULL; }
| simples B1 { 
	appendChild($1, $2);
	$$ = $1;
};

 /*    def var local    

	inicial: local
	terminais: L3, L4, L6

 */

local: L1 { $$ = $1; }
| TK_PR_STATIC L1 { $$ = $2; }
| TK_PR_CONST L1 { $$ = $2; }
| TK_PR_STATIC TK_PR_CONST L1 { $$ = $3; };
L1: tipo L2 { $$ = $2; };
L2: TK_IDENTIFICADOR L3 { 
	if ($2 == NULL) {
		$$ = NULL;
	} else {
		AST *node = createNode($1);
		prependChild($2, node);
		$$ = $2;
	}
};
L3: ';' { $$ = NULL; }
| TK_OC_LE L4 { 
	AST *root = createNodeNoLexicalValue(initializerType);
	appendChild(root, $2);
	$$ = root;
}
| ',' L5 { $$ = NULL; };
L4: TK_IDENTIFICADOR ';' { $$ = createNode($1); }
| literal ';' { $$ = $1; };
L5: TK_IDENTIFICADOR L6 { $$ = NULL; };
L6: ',' L5 { $$ = NULL; }
| ';' { $$ = NULL; };

 /*    def atribuicao    

	inicial: att
	terminais: A2

 */

att: 
TK_IDENTIFICADOR '=' A2 { 
	
	AST *rootNode = createNodeNoLexicalValue(attributionType); 
	AST *identNode = createNode($1);
	
	appendChild(rootNode, identNode);
	appendChild(rootNode, $3);

	$$ =  rootNode;

}
| TK_IDENTIFICADOR '[' expressao ']' '=' A2 { 

	AST *rootNode = createNodeNoLexicalValue(attributionType); 
	AST *indexerNode = createNodeNoLexicalValue(indexerType);
	AST *identNode = createNode($1);
	
	appendChild(rootNode, indexerNode);
	appendChild(indexerNode, identNode);
	appendChild(indexerNode, $3);
	appendChild(rootNode, $6);

	$$ = rootNode;

};
A2: expressao { $$ = $1; };


 /*    def IO    

	inicial: io
	terminais: entrada saida

 */

io: entrada { $$ = $1; }
| saida { $$ = $1; };

entrada: TK_PR_INPUT TK_IDENTIFICADOR ';' { 
	AST *inputNode = createNodeNoLexicalValue(inputType);
	AST *identifier =  createNode($2);
	appendChild(inputNode, identifier);
	$$ = inputNode;
};

saida: TK_PR_OUTPUT TK_IDENTIFICADOR ';' { 
	AST *outputNode = createNodeNoLexicalValue(outputType);
	AST *identifier =  createNode($2);
	appendChild(outputNode, identifier);
	$$ = outputNode;
}

| TK_PR_OUTPUT literal ';' {
	AST *outputNode = createNodeNoLexicalValue(outputType);
	appendChild(outputNode, $2);
	$$ = outputNode;
};

 /*    def chamada funcao    

	inicial: chamada
	terminais: C1 C2

 */

chamada: TK_IDENTIFICADOR '(' C1 ')'
| TK_IDENTIFICADOR '(' ')';
C1: expressao | expressao C2;
C2: ',' C1;

 /*    def shift    

	inicial: shift
	terminais: S2

 */

shift: TK_IDENTIFICADOR S1;
S1: '[' expressao ']' opShift S2 | opShift S2;
S2: TK_LIT_INT ';';

/*    def retorno break e continue    

	inicial: rbc
	terminais: rbc

 */

rbc: TK_PR_RETURN expressao ';' { 
	AST *rootNode = createNodeNoLexicalValue(returnType);
	appendChild(rootNode, $2);
	$$ = rootNode;
};
rbc: TK_PR_CONTINUE ';' {
	$$ = createNodeNoLexicalValue(continueType);
};
rbc: TK_PR_BREAK ';' {	$$ = createNodeNoLexicalValue(breakType);};

 /*    def if    

	inicial: if
	terminais: if I1

 */

if: TK_PR_IF '(' expressao ')' bloco | TK_PR_IF '(' expressao ')' bloco I1;
I1: TK_PR_ELSE bloco;

 /*    def while    

	inicial: while
	terminais: while

 */

while: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco;

 /*    def for    

	inicial: for
	terminais: for

 */

for: TK_PR_FOR '(' att ':' expressao ':' att ')' bloco;

%%

int yyerror(char const *s) {

	printf("\nErro sintatico na linha %d\n", get_line_number());
	return 1;
}



