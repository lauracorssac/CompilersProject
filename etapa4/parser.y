/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

%{

#include <stdio.h>
#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"
#include "SymbolTableStack.hpp"
#include <iostream>

#define YYDEBUG 1

extern "C" {
	#include "SyntacticalType.h"
	#include "AST.h"
	#include "LexicalValue.h"
	int yyparse(void);
	int yylex(void);  
	int yywrap() {
		return 1;
	}

}

int yyerror (char const *s);
extern int get_line_number(void);
extern void *arvore;
extern SymbolTableStack tableStack;
extern SyntacticalType lastDeclaredType;

%}

%union {
	struct LexicalValue *lexicalValue;
	struct AST *node;
	int syntacticalType;
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
%type<node> FUNC_PARAM_LIST
%type<node> FUNC_BLOCK
%type<node> FUNC3
%type<node> FUNC_HEADER

%type<node> LOCAL1
%type<node> LOCAL2
%type<node> LOCAL4

%type<node> IF1
%type<node> SHIFT1
%type<node> ATT1
%type<node> FCALL1
%type<node> SIMPLECMD1

%type<node> PROGRAM
%type<syntacticalType> TYPE

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
TYPE : TK_PR_INT { $$ = intSType; }
| TK_PR_FLOAT { $$ = floatSType; }
| TK_PR_BOOL { $$ = boolSType; }
| TK_PR_CHAR { $$ = charSType; }
| TK_PR_STRING { $$ = stringSType; };

 /* definicao literais */
LITERAL: TK_LIT_INT { $$ = createNodeNoTypeWithSType($1, intSType); tableStack.insertLiteral(get_line_number(), 0, $1, intSType); }
| TK_LIT_FLOAT { $$ = createNodeNoTypeWithSType($1, floatSType); tableStack.insertLiteral(get_line_number(), 0, $1, floatSType); }
| TK_LIT_FALSE { $$ = createNodeNoTypeWithSType($1, boolSType); tableStack.insertLiteral(get_line_number(), 0, $1, boolSType); }
| TK_LIT_TRUE { $$ = createNodeNoTypeWithSType($1, boolSType); tableStack.insertLiteral(get_line_number(), 0, $1, boolSType); }
| TK_LIT_CHAR { $$ = createNodeNoTypeWithSType($1, charSType); tableStack.insertLiteral(get_line_number(), 0, $1, charSType); }
| TK_LIT_STRING { $$ = createNodeNoTypeWithSType($1, stringSType); tableStack.insertLiteral(get_line_number(), 0, $1, stringSType); };

LITERALNUM: TK_LIT_INT { $$ = createNodeNoTypeWithSType($1, intSType); tableStack.insertLiteral(get_line_number(), 0, $1, intSType); }
| TK_LIT_FLOAT { $$ = createNodeNoTypeWithSType($1, floatSType); tableStack.insertLiteral(get_line_number(), 0, $1, floatSType);};
LITERALBOOL: TK_LIT_TRUE { $$ = createNodeNoTypeWithSType($1, boolSType); tableStack.insertLiteral(get_line_number(), 0, $1, boolSType);  }
| TK_LIT_FALSE { $$ = createNodeNoTypeWithSType($1, boolSType); tableStack.insertLiteral(get_line_number(), 0, $1, boolSType); };


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
| TK_IDENTIFICADOR { 
	$$ = createNodeNoType($1); 
	tableStack.verifyIdentificatorNode($$);
}
| TK_IDENTIFICADOR '[' EXPRESSION ']' { 
	AST *rootNode = createNodeNoLexicalValue(indexerType);
	AST *identNode = createNodeNoType($1);
	appendChild(rootNode, identNode);
	appendChild(rootNode, $3);
	$$ = rootNode;

	tableStack.verifyVectorNode(identNode, rootNode, $3);
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

	tableStack.makeTernaryOperation($1, rootNode, $3, $5);

};
EXP1: EXP2 { $$ = $1; }
| EXP1 opNivel9 EXP2 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
};
EXP2: EXP3 { $$ = $1; }
| EXP2 opNivel8 EXP3 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
};
EXP3: EXP4 { $$ = $1; }
| EXP3 opNivel7 EXP4 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
};
EXP4: EXP5 { $$ = $1; }
 /* recursao invertida
	& eh o unico binario recursivo a direita
 */
| EXP5 opNivel6 EXP4 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2; 

	tableStack.makeBinaryOperation($1, $2, $3);
};
EXP5: EXP6 { $$ = $1; }
| EXP5 opNivel5 EXP6 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
};
EXP6: EXP7 { $$ = $1; }
| EXP6 opNivel4 EXP7 {
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
};
EXP7: EXP8 { $$ = $1; }
| EXP7 opNivel3 EXP8 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
};
EXP8: EXP9 { $$ = $1; }
| EXP8 opNivel2 EXP9 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
};
EXP9: EXP10 { $$ = $1; }
| EXP9 opNivel1 EXP10 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
 };
EXP10: EXP11 { $$ = $1; }
| opUnary EXP11 { 
	appendChild($1, $2);
	$$ = $1;

	tableStack.makeUnaryOperation($2, $1);
};
EXP11: OPERAND { $$ = $1; }
| '(' EXPRESSION ')' { 
	$$ = $2; 
};

 /*    def variavel global    
	
	inicial: GLOBAL
	terminais: GLOBAL3

 */
GLOBAL: TK_PR_STATIC GLOBAL1 | GLOBAL1;
GLOBAL1: TYPE GLOBAL2 { 
	SyntacticalType tipo = (SyntacticalType) $1;
	tableStack.updateTypeOfVariablesWithPendantTypes(tipo);
};
GLOBAL2: TK_IDENTIFICADOR GLOBAL3 { 
	tableStack.insertVariableWithPendantType(get_line_number(), 0, $1);
}
| TK_IDENTIFICADOR '[' TK_LIT_INT ']' GLOBAL3 { 
	int indexerValue = $3->literalTokenValueAndType.value.integerValue;
	tableStack.insertVectorWithPendantType(get_line_number(), 0, $1, indexerValue);
	//TODO: inserir aqui o literal int??
};
 /*    terminais da global    */
GLOBAL3 : ';' 
| ',' GLOBAL2;

 /*    def FUNC    
	
	inicial: FUNC
	terminais: FUNC6 FUNC4

 */


FUNC_HEADER: TYPE TK_IDENTIFICADOR {
	AST *rootNode = createNodeWithLexicalTypeAndValue(functionType, $2);
	tableStack.insertFunction($2->lineNumber, 0, rootNode, (SyntacticalType) $1);
	$$ = rootNode;
}
FUNC: TK_PR_STATIC FUNC1 { $$ = $2; }
| FUNC1 { $$ = $1; };
FUNC1: FUNC_HEADER FUNC3 {
	appendChild($1, $2);
	$$ = $1;
	
};
FUNC3: '(' ')' BLOCK  { $$ = $3; }
| PARAM_LIST_BEGIN FUNC_PARAM_LIST PARAM_LIST_END FUNC_BLOCK  { $$ = $4; };

FUNC_PARAM_LIST: TYPE TK_IDENTIFICADOR { 
	tableStack.insertParameterWithType(get_line_number(), 0, $2, (SyntacticalType) $1);
	$$ = NULL; 
}
| TK_PR_CONST TYPE TK_IDENTIFICADOR { 
	tableStack.insertParameterWithType(get_line_number(), 0, $3, (SyntacticalType) $2);
	$$ = NULL; 
}
| FUNC_PARAM_LIST ',' TYPE TK_IDENTIFICADOR { 
	tableStack.insertParameterWithType(get_line_number(), 0, $4, (SyntacticalType) $3);
	$$ = NULL;
}
| FUNC_PARAM_LIST ',' TK_PR_CONST TYPE TK_IDENTIFICADOR { 
	tableStack.insertParameterWithType(get_line_number(), 0, $5, (SyntacticalType) $4);
	$$ = NULL; 
};

FUNC_BLOCK: '{' BLOCK1 {$$ = $2;};
PARAM_LIST_BEGIN: '(' { tableStack.beginNewScope(); };
PARAM_LIST_END: ')'  { tableStack.updateFunctionWithPendantParameters(); };


 /*    def BLOCK   
	
	inicial: BLOCK
	terminais: BLOCK1

 */

BLOCK_BEGIN: '{' { tableStack.beginNewScope(); };

BLOCK: BLOCK_BEGIN BLOCK1 { 
	$$ = $2;
};
BLOCK1: '}' { 
	$$ = NULL; 
	tableStack.endLastScope();
}
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
	terminais: LOCAL2, LOCAL4

 */

LOCAL: LOCAL1 { $$ = $1; }
| TK_PR_STATIC LOCAL1 { $$ = $2; }
| TK_PR_CONST LOCAL1 { $$ = $2; }
| TK_PR_STATIC TK_PR_CONST LOCAL1 { $$ = $3; };

LOCAL1: TYPE LOCAL2 { 
	SyntacticalType tipo = (SyntacticalType) $1;
	tableStack.updateTypeOfVariablesWithPendantTypes(tipo);
	$$ = $2; 
}
| TYPE TK_IDENTIFICADOR TK_OC_LE LOCAL4 { 
	AST *root = createNodeWithLexicalTypeAndValue(initializerType, $3);
	AST *indentNode = createNodeNoTypeWithSType($2, (SyntacticalType)$1);
	tableStack.insertVariableWithType(get_line_number(), 0, $2, (SyntacticalType) $1);
	
	appendChild(root, $4);
	prependChild(root, indentNode);
	$$ = root;

	tableStack.makeInitialization(indentNode, root, $4, get_line_number());
	//root.type = type
	//se for realizada uma coersão de tipo, o que tem que atualizar? Os nodos? A tabela de simbolos?
	//se der wrong type, qual o tipo do OC_LE?

};

LOCAL2: TK_IDENTIFICADOR { 
	tableStack.insertVariableWithPendantType(get_line_number(), 0, $1);
	$$ = NULL;
} 
| LOCAL2 ',' TK_IDENTIFICADOR { 
	tableStack.insertVariableWithPendantType(get_line_number(), 0, $3);
	$$ = NULL;
};

/* valor da atribuicao */
LOCAL4: TK_IDENTIFICADOR { $$ = createNodeNoType($1); tableStack.verifyIdentificatorNode($$); }
| LITERAL { $$ = $1; };


 /*    def atribuicao    

	inicial: ATT
	terminais: ATT1

 */

ATT: 
TK_IDENTIFICADOR '=' ATT1 { 
	
	AST *rootNode = createNodeWithLexicalTypeAndValue(attributionType, $2); 
	AST *identNode = createNodeNoType($1);
	
	appendChild(rootNode, $3);
	prependChild(rootNode, identNode);
	$$ =  rootNode;

	tableStack.makeAttributionVariable(identNode, rootNode, $3, get_line_number());

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

	tableStack.makeAttributionVector(identNode, rootNode, $6, indexerNode, $3, get_line_number());
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

	tableStack.makeInput(inputNode, identifier);
};

OUTPUT: TK_PR_OUTPUT TK_IDENTIFICADOR { 
	AST *outputNode = createNodeNoLexicalValue(outputType);
	AST *identifier =  createNodeNoType($2);
	appendChild(outputNode, identifier);
	$$ = outputNode;

	tableStack.makeOutputIdentifier(outputNode, identifier);
}

| TK_PR_OUTPUT LITERAL {
	AST *outputNode = createNodeNoLexicalValue(outputType);
	appendChild(outputNode, $2);
	$$ = outputNode;

	tableStack.makeOutputLiteral(outputNode, $2);
};

 /*    def chamada funcao    

	inicial: FCALL
	terminais: FCALL1

 */

FCALL: TK_IDENTIFICADOR '(' FCALL1 ')' { 
	AST *rootNode = createNodeWithLexicalTypeAndValue(functionCallType, $1);
	appendChild(rootNode, $3);
	$$ = rootNode;

	tableStack.makeFunctionCall(rootNode, $3);
}
| TK_IDENTIFICADOR '(' ')' {
	$$ = createNodeWithLexicalTypeAndValue(functionCallType, $1);

	tableStack.makeFunctionCall($$, NULL);
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

	tableStack.verifyIdentificatorNode(identNode);
	tableStack.makeShift($2, $3);
} 
| TK_IDENTIFICADOR '[' EXPRESSION ']' opShift SHIFT1 { 

	AST *identNode = createNodeNoType($1);
	AST *indexerNode = createNodeNoLexicalValue(indexerType);

	appendChild(indexerNode, identNode); 
	appendChild(indexerNode, $3); //expressao

	appendChild($5, indexerNode);
	appendChild($5, $6); //S2

	$$ = $5; //opShift

	tableStack.verifyVectorNode(identNode, indexerNode, $6);
	tableStack.makeShift($5, $6);
};
SHIFT1: TK_LIT_INT { 
	$$ = createNodeNoType($1);
 };

/*    def retorno break e continue    

	inicial: RBC
	terminais: RBC

 */

RBC: TK_PR_RETURN EXPRESSION { 
	AST *rootNode = createNodeNoLexicalValue(returnType);
	appendChild(rootNode, $2);
	$$ = rootNode;

	tableStack.makeReturn(rootNode, $2);
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



