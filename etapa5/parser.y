/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

%{

#include <stdio.h>
#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"
#include "SymbolTableStack.hpp"
#include "CodeGenerator.hpp"
#include <iostream>

#define YYDEBUG 1

#include "SyntacticalType.hpp"
#include "AST.hpp"
#include "Utils.hpp"
#include "LexicalValue.hpp"
extern "C" {
	
	int yyparse(void);
	int yylex(void);  
	int yywrap() {
		return 1;
	}

}

int yyerror (char const *s);
extern CodeGenerator codeGenerator;
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
%type<node> DECIDENTIFIER
%type<node> DECVECTOR

%type<node> ATT
%type<node> BLOCK
%type<node> CMDLIST
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
		codeGenerator.appendCode($1, $2);
		$$ = $1;
	}
	
	codeGenerator.restartRegisterNumber();
}
| { $$ = NULL; };

 /* definicao tipos */
TYPE : TK_PR_INT { $$ = intSType; }
| TK_PR_FLOAT { $$ = floatSType; }
| TK_PR_BOOL { $$ = boolSType; }
| TK_PR_CHAR { $$ = charSType; }
| TK_PR_STRING { $$ = stringSType; };

 /* definicao literais */
LITERAL: LITERALNUM
| LITERALBOOL
| TK_LIT_CHAR { $$ = createNodeNoTypeWithSType($1, charSType); tableStack.insertLiteral(get_line_number(), 0, $1, charSType); }
| TK_LIT_STRING { $$ = createNodeNoTypeWithSType($1, stringSType); tableStack.insertLiteral(get_line_number(), 0, $1, stringSType); };

LITERALNUM: TK_LIT_INT { $$ = createNodeNoTypeWithSType($1, intSType); tableStack.insertLiteral(get_line_number(), 0, $1, intSType); codeGenerator.makeLiteralCode($$);}
| TK_LIT_FLOAT { $$ = createNodeNoTypeWithSType($1, floatSType); tableStack.insertLiteral(get_line_number(), 0, $1, floatSType); codeGenerator.makeLiteralCode($$);};
LITERALBOOL: TK_LIT_TRUE { $$ = createNodeNoTypeWithSType($1, boolSType); tableStack.insertLiteral(get_line_number(), 0, $1, boolSType); codeGenerator.makeLiteralCode($$);}
| TK_LIT_FALSE { $$ = createNodeNoTypeWithSType($1, boolSType); tableStack.insertLiteral(get_line_number(), 0, $1, boolSType); codeGenerator.makeLiteralCode($$);};

/* Definição de um identificador declarado (aka variável) */
DECIDENTIFIER: TK_IDENTIFICADOR { 
	$$ = createNodeNoType($1); 
	tableStack.verifyIdentificatorNode($$);
	OffsetAndScope offsetAndScope = tableStack.getUpdatedOffsetAndScopeForVariable($$);
	codeGenerator.makeDeclaredVariable($$, offsetAndScope);
}

/* Definição de um vetor declarado */
DECVECTOR: TK_IDENTIFICADOR '[' EXPRESSION ']' {

	AST *rootNode = createNodeNoLexicalValue(indexerType);
	AST *identNode = createNodeNoType($1);
	appendChild(rootNode, identNode);
	appendChild(rootNode, $3);
	$$ = rootNode;

	tableStack.verifyVectorNode(identNode, rootNode, $3);
}

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
| DECIDENTIFIER { $$ = $1; }
| DECVECTOR { $$ = $1; } 
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
opNivel2: '*' { $$ = createNodeNoType($1); $$->nodeInstructionType = mult; };
| '/' { $$ = createNodeNoType($1); $$->nodeInstructionType = _div; };
| '%' { $$ = createNodeNoType($1); };
opNivel3: '+' { $$ = createNodeNoType($1); $$->nodeInstructionType = add; };
| '-' { $$ = createNodeNoType($1); $$->nodeInstructionType = sub; };

 /* relacionais */
opNivel4: TK_OC_LE { $$ = createNodeNoType($1); $$->nodeInstructionType = cmp_LE; }
| TK_OC_GE { $$ = createNodeNoType($1); $$->nodeInstructionType = cmp_GE; }
| '<' { $$ = createNodeNoType($1); $$->nodeInstructionType = cmp_LT; }
| '>' { $$ = createNodeNoType($1); $$->nodeInstructionType = cmp_GT; };

/* equalidade */
opNivel5: TK_OC_EQ { $$ = createNodeNoType($1); $$->nodeInstructionType = cmp_EQ;}
| TK_OC_NE { $$ = createNodeNoType($1); $$->nodeInstructionType = cmp_NE; };

 /* bitwise and */
opNivel6: '&' { $$ = createNodeNoType($1); };

/* bitwise or */
opNivel7: '|' { $$ = createNodeNoType($1); };

 /* logical and */ 
opNivel8: TK_OC_AND { $$ = createNodeNoType($1); };

 /* logical or */
opNivel9: TK_OC_OR { $$ = createNodeNoType($1); };

 /* operadores unarios */
opUnary: '-' { $$ = createNodeNoType($1); $$->nodeType = subType; }
| '+' { $$ = createNodeNoType($1); }
| '*' { $$ = createNodeNoType($1); }
| '&' { $$ = createNodeNoType($1); }
| '#' { $$ = createNodeNoType($1); }
| '!' { $$ = createNodeNoType($1); $$->nodeType = notType; }
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
	codeGenerator.makeTernaryOperation($1, rootNode, $3, $5);

};
EXP1: EXP2 { $$ = $1; }
| EXP1 opNivel9 EXP2 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
	codeGenerator.makeOr($1, $2, $3);
};
EXP2: EXP3 { $$ = $1; }
| EXP2 opNivel8 EXP3 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
	codeGenerator.makeAnd($1, $2, $3); 
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
	codeGenerator.makeBinaryOperation($1, $2, $3);
};
EXP6: EXP7 { $$ = $1; }
| EXP6 opNivel4 EXP7 {
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
	codeGenerator.makeBinaryOperation($1, $2, $3);
};
EXP7: EXP8 { $$ = $1; }
| EXP7 opNivel3 EXP8 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
	codeGenerator.makeBinaryOperation($1, $2, $3);
};
EXP8: EXP9 { $$ = $1; }
| EXP8 opNivel2 EXP9 { 
	appendChild($2, $1);
	appendChild($2, $3);
	$$ = $2;

	tableStack.makeBinaryOperation($1, $2, $3);
	codeGenerator.makeBinaryOperation($1, $2, $3);
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
	codeGenerator.makeUnaryOperation($2, $1);
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
	tableStack.insertVariableWithPendantType($1->lineNumber, 0, $1);
}
| TK_IDENTIFICADOR '[' TK_LIT_INT ']' GLOBAL3 { 
	int indexerValue = $3->literalTokenValueAndType.value.integerValue;
	tableStack.insertVectorWithPendantType($1->lineNumber, 0, $1, indexerValue);
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

FUNC1: FUNC_HEADER '(' ')' BLOCK  { 
	appendChild($1, $4);
	$$ = $1;
	
	// gets space for local variables 
	int offsetLocalVariables = tableStack.getLastFunctionOffset();
	// gets initial instruction label of function
	int label= tableStack.getLabelForFunction($1);
	// generates code for function
	codeGenerator.makeFunction($1, offsetLocalVariables, 0, label, $4);

	//default return
	//in case the function doesnt contain any return expression
	if (($4 == NULL || $4->numberOfReturnStatements == 0)) {
		int offsetRetValue = tableStack.getReturnValueOffsetForLastDeclaredFunction();
		codeGenerator.makeEmptyReturn($1, offsetRetValue);
	} 

}
| FUNC_HEADER PARAM_LIST_BEGIN FUNC_PARAM_LIST PARAM_LIST_END FUNC_BLOCK {
	appendChild($1, $5);
	$$ = $1;

	// gets space for local variables 
	int offsetLocalVariables = tableStack.getLastFunctionOffset();
	// gets initial instruction label of function
	int label= tableStack.getLabelForFunction($1);
	// gets quantity of parameters
	int quantityOfParameters = tableStack.getQuantityOfParametersForFunction($1);
	// generates code for function
	codeGenerator.makeFunction($1, offsetLocalVariables, quantityOfParameters, label, $5);

	//default return
	//in case the function doesnt contain any return expression
	if (($5 == NULL || $5->numberOfReturnStatements == 0)) {
		int offsetRetValue = tableStack.getReturnValueOffsetForLastDeclaredFunction();
		codeGenerator.makeEmptyReturn($1, offsetRetValue);
	} 

};

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

FUNC_BLOCK: '{' CMDLIST BLOCK_END { $$ = $2; };
PARAM_LIST_BEGIN: '(' { tableStack.beginNewScope(); };
PARAM_LIST_END: ')'  { tableStack.updateFunctionWithPendantParameters(); };


 /*    def BLOCK   
	
	inicial: BLOCK
	terminais: BLOCK

 */

BLOCK_BEGIN: '{' { tableStack.beginNewScope(); };
BLOCK_END: '}' { tableStack.endLastScope();}


BLOCK: BLOCK_BEGIN CMDLIST BLOCK_END { 
	$$ = $2;
};
CMDLIST:
CMDLIST SIMPLECMD { 

	// if both nodes are null
	if ($1 == NULL && $2 == NULL) { 
		$$ = NULL;
	} 
	
	// both nodes not null
	else if ($2 != NULL && $1 != NULL) { 
		appendChild($1, $2);
		codeGenerator.appendCode($1, $2);
		$$ = $1;		
		$$->numberOfReturnStatements += $2->numberOfReturnStatements;
	} 
	
	// only 2 is NULL
	else if ($1 != NULL) {
		$$ = $1;
	} 
	
	// only 1 is NULL
	else {
		$$ = $2;
	}
}
| {$$ = NULL;};

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
	AST *identNode = createNodeNoTypeWithSType($2, (SyntacticalType)$1);
	tableStack.insertVariableWithType($2->lineNumber, 0, $2, (SyntacticalType) $1);
	
	appendChild(root, $4);
	prependChild(root, identNode);
	$$ = root;

	tableStack.makeInitialization(identNode, root, $4);
	
	OffsetAndScope offsetAndScope = tableStack.getUpdatedOffsetAndScopeForVariable(identNode);
	codeGenerator.makeAttributionLocalVariable(root, $4, offsetAndScope);

};

LOCAL2: TK_IDENTIFICADOR { 
	tableStack.insertVariableWithPendantType($1->lineNumber, 0, $1);
	$$ = NULL;
} 
| LOCAL2 ',' TK_IDENTIFICADOR { 
	tableStack.insertVariableWithPendantType($3->lineNumber, 0, $3);
	$$ = NULL;
};

/* valor da atribuicao */
LOCAL4: DECIDENTIFIER { $$ = $1; }
| LITERAL { $$ = $1; };


 /*    def atribuicao    

	inicial: ATT
	terminais: ATT1

 */

ATT: 
DECIDENTIFIER '=' ATT1 { 
	
	AST *rootNode = createNodeWithLexicalTypeAndValue(attributionType, $2); 
	
	appendChild(rootNode, $3);
	prependChild(rootNode, $1);
	$$ = rootNode;

	tableStack.makeAttributionVariable($1, rootNode, $3);

	OffsetAndScope offsetAndScope = tableStack.getUpdatedOffsetAndScopeForVariable($1);
	codeGenerator.makeAttributionLocalVariable(rootNode, $3, offsetAndScope);

}
| DECVECTOR '=' ATT1 { 

	AST *rootNode = createNodeWithLexicalTypeAndValue(attributionType, $2); 
	appendChild(rootNode, $1);
	appendChild(rootNode, $3);
	$$ = rootNode;

	tableStack.makeAttributionVector(rootNode, $3, $1);
};
ATT1: EXPRESSION { $$ = $1; };


 /*    def IO    

	inicial: IO
	terminais: INPUT OUTPUT

 */

IO: INPUT { $$ = $1; }
| OUTPUT { $$ = $1; };

INPUT: TK_PR_INPUT DECIDENTIFIER { 
	AST *inputNode = createNodeNoLexicalValue(inputType); 
	appendChild(inputNode, $2);
	$$ = inputNode;

	tableStack.makeInput(inputNode, $2);
};

OUTPUT: TK_PR_OUTPUT DECIDENTIFIER { 
	AST *outputNode = createNodeNoLexicalValue(outputType);
	appendChild(outputNode, $2);
	$$ = outputNode;

	tableStack.makeOutputIdentifier(outputNode, $2);
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

	string functionName = stringFromLiteralValue($1->literalTokenValueAndType);
	int offset = tableStack.getReturnValueOffsetForFunction(functionName);
	int functionLabel = tableStack.getLabelForFunction(rootNode);
	int quantityOfParameters = tableStack.getQuantityOfParametersForFunction(functionName);
	
	codeGenerator.makeFunctionCall(rootNode, $3, functionLabel, offset, quantityOfParameters);

}
| TK_IDENTIFICADOR '(' ')' {
	$$ = createNodeWithLexicalTypeAndValue(functionCallType, $1);
	tableStack.makeFunctionCall($$, NULL);

	string functionName = stringFromLiteralValue($1->literalTokenValueAndType);
	int offset = tableStack.getReturnValueOffsetForFunction(functionName);
	int functionLabel = tableStack.getLabelForFunction($$);
	
	codeGenerator.makeFunctionCall($$, NULL, functionLabel, offset, 0);

};
FCALL1: EXPRESSION { $$ = $1; $$->numberOfParameters = 1;}
| FCALL1 ',' EXPRESSION {
	appendChild($1, $3);
	$$ = $1;
	$$->numberOfParameters += 1;
};

 /*    def shift    

	inicial: shift
	terminais: S2

 */

SHIFT: DECIDENTIFIER opShift SHIFT1 {

	appendChild($2, $1);
	appendChild($2, $3); 

	$$ = $2;

	tableStack.makeShift($2, $3);
} 
| DECVECTOR opShift SHIFT1 { 

	appendChild($2, $1);
	appendChild($2, $3);

	$$ = $2;

	tableStack.makeShift($2, $3);
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

	int functionLabel = tableStack.getLabelForLastDeclaredFunction();
	tableStack.makeReturn(rootNode, $2);

	// function main doesnt have to have a return statement
	//if (functionLabel != 0) {
		int offset = tableStack.getReturnValueOffsetForLastDeclaredFunction();
		codeGenerator.makeReturn(rootNode, $2, offset);
		$$->numberOfReturnStatements = 1;
	//}
	
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

	codeGenerator.makeIf(rootNode, $3, $5, NULL);

}
| TK_PR_IF '(' EXPRESSION ')' BLOCK IF1 { 
	AST *rootNode = createNodeNoLexicalValue(ifType);
	appendChild(rootNode, $3);
	appendChild(rootNode, $5);
	appendChild(rootNode, $6);
	$$ = rootNode;

	codeGenerator.makeIf(rootNode, $3, $5, $6);
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

	codeGenerator.makeWhile(rootNode, $3, $6);
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

	codeGenerator.makeFor(rootNode, $3, $5, $7, $9);
};

%%

int yyerror(char const *s) {

	cout << endl;
	cout << "Erro sintatico na linha = " << get_line_number() << endl;
	return 1;
}



