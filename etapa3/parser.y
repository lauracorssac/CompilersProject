/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

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

%start PROGRAM

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

%token ',' ';' ':' '(' ')' '[' ']' '{' '}' '.' 
%token<lexicalValue> '=' '$' '+' '-' '*' '/' '%' '^' '&' '|' '<' '>' '!' '?' '#'

%type<node> LITERAL
%type<node> LITERALNUM
%type<node> LITERALBOOL
%type<node> OPERAND
%type<node> EXPRESSION

%type<node> ATT
%type<node> BLOCK
%type<node> BLOCK1
%type<node> SIMPLECMD
%type<node> LOCAL
%type<node> IO
%type<node> SHIFT
%type<node> RBC
%type<node> IF
%type<node> WHILE
%type<node> FOR
%type<node> FCALL
%type<node> FUNC
%type<node> INPUT
%type<node> OUTPUT

%type<node> opNivel1
%type<node> opNivel2
%type<node> opNivel3
%type<node> opNivel4
%type<node> opNivel5
%type<node> opNivel6
%type<node> opNivel7
%type<node> opNivel8
%type<node> opNivel9
%type<node> opUnary 
%type<node> opShift

%type<node> EXP1
%type<node> EXP2
%type<node> EXP3
%type<node> EXP4
%type<node> EXP5
%type<node> EXP6
%type<node> EXP7
%type<node> EXP8
%type<node> EXP9
%type<node> EXP10
%type<node> EXP11

%type<node> FUNC1
%type<node> FUNC2
%type<node> FUNC3
%type<node> FUNC4
%type<node> FUNC5
%type<node> FUNC6
%type<node> FUNC7

%type<node> LOCAL1
%type<node> LOCAL2
%type<node> LOCAL3
%type<node> LOCAL4
%type<node> LOCAL5
%type<node> LOCAL6

%type<node> IF1
%type<node> SHIFT1
%type<node> ATT1
%type<node> FCALL1
%type<node> SIMPLECMD1

%type<node> PROGRAM


%%

 /*    def programa    
	
	inicial: PROGRAM
	terminais: PROGRAM

 */

PROGRAM : PROGRAM GLOBAL { $$ = $1; }
| PROGRAM FUNC { 
	if ($1 == NULL) {
		arvore = (void*)$2;
		$$ = $2;
	} else {
		appendChild($1, $2);
	}
	$$ = $2;
}
| { $$ = NULL; };

 /* definicao tipos */
TYPE : TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL | TK_PR_CHAR | TK_PR_STRING;

 /* definicao literais */
LITERAL: TK_LIT_INT { $$ = createNodeNoType($1); }
| TK_LIT_FLOAT { $$ = createNodeNoType($1); }
| TK_LIT_FALSE { $$ = createNodeNoType($1); }
| TK_LIT_TRUE { $$ = createNodeNoType($1); }
| TK_LIT_CHAR { $$ = createNodeNoType($1); }
| TK_LIT_STRING { $$ = createNodeNoType($1); };
LITERALNUM: TK_LIT_INT { $$ = createNodeNoType($1); }
| TK_LIT_FLOAT { $$ = createNodeNoType($1); };
LITERALBOOL: TK_LIT_TRUE { $$ = createNodeNoType($1); }
| TK_LIT_FALSE { $$ = createNodeNoType($1); };


 /* definicao comandos simples */

SIMPLECMD: SIMPLECMD1 ';' { $$ = $1; }; 
SIMPLECMD1: BLOCK { $$ = $1; }
| LOCAL { $$ = $1; }
| ATT { $$ = $1; }
| IO { $$ = $1; }
| SHIFT { $$ = $1; }
| RBC { $$ = $1; }
| IF { $$ = $1; }
| WHILE { $$ = $1; }
| FOR { $$ = $1; }
| FCALL { $$ = $1; }; 

 /* definicao operandos aceitos em expressoes */
OPERAND: LITERALNUM { $$ = $1; }
| TK_IDENTIFICADOR { $$ = createNodeNoType($1); }
| TK_IDENTIFICADOR '[' EXPRESSION ']' { 
	AST *rootNode = createNodeNoLexicalValue(indexerType);
	AST *identNode = createNodeNoType($1);
	appendChild(rootNode, identNode);
	appendChild(rootNode, $3);
	$$ = rootNode;
} 
| FCALL { $$ = $1; }
| LITERALBOOL { $$ = $1; }; 
 
 /* def operador shift */
opShift: TK_OC_SL { $$ = createNodeNoType($1); }
| TK_OC_SR { $$ = createNodeNoType($1); };

 /*    def operadores binarios    
	
	ordem decrescente de precedencia
	opNivelX: quanto menor o X, maior a precedencia do operador

 */
opNivel1: '^' { $$ = createNodeNoType($1);};
opNivel2: '*' { $$ = createNodeNoType($1); };
| '/' { $$ = createNodeNoType($1); };
| '%' { $$ = createNodeNoType($1); };
opNivel3: '+' { $$ = createNodeNoType($1); };
| '-' { $$ = createNodeNoType($1); };

 /* relacionais */
opNivel4: TK_OC_LE { $$ = createNodeNoType($1); }
| TK_OC_GE { $$ = createNodeNoType($1); }
| '<' { $$ = createNodeNoType($1); }
| '>' { $$ = createNodeNoType($1); };

/* equalidade */
opNivel5: TK_OC_EQ { $$ = createNodeNoType($1); }
| TK_OC_NE { $$ = createNodeNoType($1); };

 /* bitwise and */
opNivel6: '&' { $$ = createNodeNoType($1); };

/* bitwise or */
opNivel7: '|' { $$ = createNodeNoType($1); };

 /* logical and */ 
opNivel8: TK_OC_AND { $$ = createNodeNoType($1); };

 /* logical or */
opNivel9: TK_OC_OR { $$ = createNodeNoType($1); };

 /* operadores unarios */
opUnary: '-' { $$ = createNodeNoType($1); }
| '+' { $$ = createNodeNoType($1); }
| '*' { $$ = createNodeNoType($1); }
| '&' { $$ = createNodeNoType($1); }
| '#' { $$ = createNodeNoType($1); }
| '!' { $$ = createNodeNoType($1); }
| '?' { $$ = createNodeNoType($1); };

 /*    def expressao    
	
	inicial: EXPRESSION
	final: E10

 */

EXPRESSION: EXP1 { $$ = $1; }
| EXPRESSION '?' EXP1 ':' EXP1 {
	freeLexicalValue($2);
	AST *rootNode = createNodeNoLexicalValue(ternaryType);
	appendChild(rootNode, $1);
	appendChild(rootNode, $3);
	appendChild(rootNode, $5);
	$$ = rootNode;
};
EXP1: EXP2 { $$ = $1; }
| EXP1 opNivel9 EXP2 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;
};
EXP2: EXP3 { $$ = $1; }
| EXP2 opNivel8 EXP3 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;
};
EXP3: EXP4 { $$ = $1; }
| EXP3 opNivel7 EXP4 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;
};
EXP4: EXP5 { $$ = $1; }
 /* recursao invertida
	& eh o unico binario recursivo a direita
 */
| EXP5 opNivel6 EXP4 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2; 
};
EXP5: EXP6 { $$ = $1; }
| EXP5 opNivel5 EXP6 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;
};
EXP6: EXP7 { $$ = $1; }
| EXP6 opNivel4 EXP7 {
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;
};
EXP7: EXP8 { $$ = $1; }
| EXP7 opNivel3 EXP8 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;
};
EXP8: EXP9 { $$ = $1; }
| EXP8 opNivel2 EXP9 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;
};
EXP9: EXP10 { $$ = $1; }
| EXP9 opNivel1 EXP10 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;
 };
EXP10: EXP11 { $$ = $1; }
| opUnary EXP11 { 
	appendChild($1, $2);
	$$ = $1;
};
EXP11: OPERAND { $$ = $1; }
| '(' EXPRESSION ')' { 
	$$ = $2; 
};

 /*    def variavel global    
	
	inicial: GLOBAL
	terminais: GLOBAL3 GLOBAL4

 */
GLOBAL: TK_PR_STATIC GLOBAL1 | GLOBAL1;
GLOBAL1 : TYPE GLOBAL2;
GLOBAL2 : TK_IDENTIFICADOR GLOBAL3 { freeLexicalValue($1); };
 /*    terminais da global    */
GLOBAL3 : ';' | ',' GLOBAL2
| '[' TK_LIT_INT ']' GLOBAL4 { 
	freeLexicalValue($2);
};
GLOBAL4 : ';' | ',' GLOBAL2;


 /*    def FUNC    
	
	inicial: FUNC
	terminais: FUNC6 FUNC4

  */
FUNC: TK_PR_STATIC FUNC1 { $$ = $2; }
| FUNC1 { $$ = $1; };
FUNC1: TYPE FUNC2 { $$ = $2; };
FUNC2: TK_IDENTIFICADOR FUNC3 { 
	AST *rootNode = createNodeWithLexicalTypeAndValue(functionType, $1);
	appendChild(rootNode, $2);
	$$ = rootNode;
};
FUNC3: '(' FUNC4 { $$ = $2; };
FUNC4: ')' BLOCK { $$ = $2; }
| TYPE FUNC5 { $$ = $2; }
| TK_PR_CONST TYPE FUNC5 { $$ = $3; };
FUNC5: TK_IDENTIFICADOR FUNC6 { freeLexicalValue($1); $$ = $2; };
FUNC6: ')' BLOCK { $$ = $2; }
| ',' FUNC7  { $$ = $2; };
FUNC7: TYPE FUNC5 { $$ = $2; }
| TK_PR_CONST TYPE FUNC5 { $$ = $3; };

 /*    def BLOCO    
	
	inicial: BLOCO
	terminais: BLOCO1

 */

BLOCK: '{' BLOCK1 { $$ = $2;};
BLOCK1: '}' { $$ = NULL; }
| SIMPLECMD BLOCK1 { 
	if ($1 != NULL){
		appendChild($1, $2);
		$$ = $1;
	} else {
		$$ = $2;
	}
};

 /*    def var LOCAL    

	inicial: LOCAL
	terminais: LOCAL2, LOCAL4, LOCAL6

 */

LOCAL: LOCAL1 { $$ = $1; }
| TK_PR_STATIC LOCAL1 { $$ = $2; }
| TK_PR_CONST LOCAL1 { $$ = $2; }
| TK_PR_STATIC TK_PR_CONST LOCAL1 { $$ = $3; };
LOCAL1: TYPE LOCAL2 { $$ = $2; };
LOCAL2: TK_IDENTIFICADOR { freeLexicalValue($1); $$ = NULL; }
| TK_IDENTIFICADOR LOCAL3 { 
	if ($2 == NULL) {
		$$ = NULL;
	} else {
		AST *node = createNodeNoType($1);
		prependChild($2, node);
		$$ = $2;
	}
};
LOCAL3: TK_OC_LE LOCAL4 { 
	AST *root = createNodeWithLexicalTypeAndValue(initializerType, $1);
	appendChild(root, $2);
	$$ = root;
}
| ',' LOCAL5 { $$ = NULL; };
LOCAL4: TK_IDENTIFICADOR { $$ = createNodeNoType($1); }
| LITERAL { $$ = $1; };
LOCAL5: TK_IDENTIFICADOR { freeLexicalValue($1); $$ = NULL; };
| TK_IDENTIFICADOR LOCAL6 { freeLexicalValue($1); $$ = NULL; };
LOCAL6: ',' LOCAL5 { $$ = NULL; };

 /*    def atribuicao    

	inicial: ATT
	terminais: ATT1

 */

ATT: 
TK_IDENTIFICADOR '=' ATT1 { 
	
	AST *rootNode = createNodeWithLexicalTypeAndValue(attributionType, $2); 
	AST *identNode = createNodeNoType($1);
	
	appendChild(rootNode, identNode);
	appendChild(rootNode, $3);

	$$ =  rootNode;

}
| TK_IDENTIFICADOR '[' EXPRESSION ']' '=' ATT1 { 

	AST *rootNode = createNodeWithLexicalTypeAndValue(attributionType, $5); 
	AST *indexerNode = createNodeNoLexicalValue(indexerType);
	AST *identNode = createNodeNoType($1);
	
	appendChild(rootNode, indexerNode);
	appendChild(indexerNode, identNode);
	appendChild(indexerNode, $3);
	appendChild(rootNode, $6);

	$$ = rootNode;

};
ATT1: EXPRESSION { $$ = $1; };


 /*    def IO    

	inicial: IO
	terminais: INPUT OUTPUT

 */

IO: INPUT { $$ = $1; }
| OUTPUT { $$ = $1; };

INPUT: TK_PR_INPUT TK_IDENTIFICADOR { 
	AST *inputNode = createNodeNoLexicalValue(inputType);
	AST *identifier =  createNodeNoType($2);
	appendChild(inputNode, identifier);
	$$ = inputNode;
};

OUTPUT: TK_PR_OUTPUT TK_IDENTIFICADOR { 
	AST *outputNode = createNodeNoLexicalValue(outputType);
	AST *identifier =  createNodeNoType($2);
	appendChild(outputNode, identifier);
	$$ = outputNode;
}

| TK_PR_OUTPUT LITERAL {
	AST *outputNode = createNodeNoLexicalValue(outputType);
	appendChild(outputNode, $2);
	$$ = outputNode;
};

 /*    def chamada funcao    

	inicial: FCALL
	terminais: FCALL1

 */

FCALL: TK_IDENTIFICADOR '(' FCALL1 ')' { 
	AST *rootNode = createNodeWithLexicalTypeAndValue(functionCallType, $1);
	appendChild(rootNode, $3);
	$$ = rootNode;
}
| TK_IDENTIFICADOR '(' ')' {
	$$ = createNodeWithLexicalTypeAndValue(functionCallType, $1);
};
FCALL1: EXPRESSION { $$ = $1; }
| EXPRESSION ',' FCALL1 {
	appendChild($1, $3);
	$$ = $1;
};

 /*    def shift    

	inicial: shift
	terminais: S2

 */

SHIFT: TK_IDENTIFICADOR opShift SHIFT1 {

	AST *identNode = createNodeNoType($1);
	appendChild($2, identNode); 
	appendChild($2, $3); //S2

	$$ = $2; //opShift
} 
| TK_IDENTIFICADOR '[' EXPRESSION ']' opShift SHIFT1 { 

	AST *identNode = createNodeNoType($1);
	AST *indexerNode = createNodeNoLexicalValue(indexerType);

	appendChild(indexerNode, identNode); 
	appendChild(indexerNode, $3); //expressao

	appendChild($5, indexerNode);
	appendChild($5, $6); //S2

	$$ = $5; //opShift
};
SHIFT1: TK_LIT_INT { $$ = createNodeNoType($1); };

/*    def retorno break e continue    

	inicial: RBC
	terminais: RBC

 */

RBC: TK_PR_RETURN EXPRESSION { 
	AST *rootNode = createNodeNoLexicalValue(returnType);
	appendChild(rootNode, $2);
	$$ = rootNode;
}
| TK_PR_CONTINUE {
	$$ = createNodeNoLexicalValue(continueType);
}
| TK_PR_BREAK {	$$ = createNodeNoLexicalValue(breakType);};

 /*    def IF    

	inicial: IF
	terminais: IF IF1

 */

IF: TK_PR_IF '(' EXPRESSION ')' BLOCK { 
	AST *rootNode = createNodeNoLexicalValue(ifType);
	appendChild(rootNode, $3);
	appendChild(rootNode, $5);
	$$ = rootNode;
}
| TK_PR_IF '(' EXPRESSION ')' BLOCK IF1 { 
	AST *rootNode = createNodeNoLexicalValue(ifType);
	appendChild(rootNode, $3);
	appendChild(rootNode, $5);
	appendChild(rootNode, $6);
	$$ = rootNode;
};
IF1: TK_PR_ELSE BLOCK {
	$$ = $2;
};

 /*    def WHILE    

	inicial: WHILE
	terminais: WHILE

 */

WHILE: TK_PR_WHILE '(' EXPRESSION ')' TK_PR_DO BLOCK {
	AST *rootNode = createNodeNoLexicalValue(whileType);
	appendChild(rootNode, $3);
	appendChild(rootNode, $6);
	$$ = rootNode;
};

 /*    def FOR    

	inicial: FOR
	terminais: FOR

 */

FOR: TK_PR_FOR '(' ATT ':' EXPRESSION ':' ATT ')' BLOCK {
	AST *rootNode = createNodeNoLexicalValue(forType);
	appendChild(rootNode, $3); //ATT
	appendChild(rootNode, $5); //EXPRESSION
	appendChild(rootNode, $7); //ATT
	appendChild(rootNode, $9); //BLOCO
	$$ = rootNode;
};

%%

int yyerror(char const *s) {

	printf("\nErro sintatico na linha %d\n", get_line_number());
	return 1;
}



