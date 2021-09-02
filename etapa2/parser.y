%{
#include <stdio.h>
int yylex(void);
int yyerror (char const *s);
extern int get_line_number(void);
%}

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
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

%left NEG
%left POINTER
%left ADDRESS
%left PLUS
%left HASHTAG
%left INVERTBOOL
%left EVALBOOL

%right HASHTAGRIGHT
%right STARRIGHT
%right AMPERSANDRIGHT

%%
tipo : TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL | TK_PR_CHAR | TK_PR_STRING;
literal: TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_FALSE | TK_LIT_TRUE | TK_LIT_CHAR | TK_LIT_STRING;
literalNum: TK_LIT_INT | TK_LIT_FLOAT;
literalBool: TK_LIT_TRUE | TK_LIT_FALSE;

simples: bloco ';' | local | att ';' | io | shift | rbc | if | while | for | chamada ';'; 
indexador: '[' TK_LIT_INT ']';

operando: literalNum | TK_IDENTIFICADOR | TK_IDENTIFICADOR indexador | chamada | literalBool; 
opShift: TK_OC_SL | TK_OC_SR;

 /*    def operadores binarios    
	
	opNivelX: quanto menor o X, maior a precedencia do operador
 */
opNivel1: '^';
opNivel2: '*' | '/' | '%';
opNivel3: '+' | '-';

 /* relacionais */
opNivel4: TK_OC_LE | TK_OC_GE | TK_OC_EQ | TK_OC_NE | '<' | '>';

 /* bitwise and, bitwise or */
opNivel5: '&' | '|';

 /* and, or */ 
opNivel6: TK_OC_AND | TK_OC_OR; 

 /*    def expressao    
	
	inicial: expressao
	final: E6

 */

expressao: E0 | expressao '?' E0 ':' E0;
E0: E1 | E0 opNivel6 E1; 
E1: E2 | E1 opNivel5 E2;
E2: E3 | E2 opNivel4 E3;
E3: E4 | E3 opNivel3 E4;
E4: E5 | E4 opNivel2 E5;
E5: E6 | E5 opNivel1 E6;
E6: operando | '(' expressao ')'; 
E6: '-' E6 %prec NEG;
E6: '+' E6 %prec PLUS;
E6: '*' E6 %prec POINTER;
E6: '&' E6 %prec ADDRESS;
E6: '#' E6 %prec HASHTAG;
E6: '!' E6 %prec INVERTBOOL;
E6: '?' E6 %prec EVALBOOL;

programa : global | funcao | programa global | programa funcao;

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
funcao: TK_PR_STATIC F1 | F1;
F1: tipo F2;
F2: TK_IDENTIFICADOR F3;
F3: '(' F4;
F4: ')' bloco | tipo F5 | TK_PR_CONST tipo F5;
F5: TK_IDENTIFICADOR F6;
F6: ')' bloco | ',' F7;
F7: tipo F5 | TK_PR_CONST tipo F5;

 /*    def bloco    
	
	inicial: bloco
	terminais: B1

 */

bloco: '{' B1
B1: '}' | simples B1;


 /*    def var local    

	inicial: local
	terminais: L3, L4, L6

 */

local: L1 | TK_PR_STATIC L1 | TK_PR_CONST L1 | TK_PR_STATIC TK_PR_CONST L1;
L1: tipo L2;
L2: TK_IDENTIFICADOR L3;
L3: ';' | TK_OC_LE L4 | ',' L5;
L4: TK_IDENTIFICADOR ';' | literal ';' ;
L5: TK_IDENTIFICADOR L6;
L6: ',' L5 | ';';

 /*    def atribuicao    

	inicial: att
	terminais: A2

 */

att: TK_IDENTIFICADOR A1
A1: '=' A2 | '[' expressao ']' '=' A2;
A2: expressao;


 /*    def IO    

	inicial: io
	terminais: entrada saida

 */

io: entrada | saida;
entrada: TK_PR_INPUT TK_IDENTIFICADOR ';'
saida: TK_PR_OUTPUT TK_IDENTIFICADOR ';' | TK_PR_OUTPUT literal ';'

 /*    def chamada funcao    

	inicial: chamada
	terminais: C1 C2

 */

chamada: TK_IDENTIFICADOR '(' C1 ')' | TK_IDENTIFICADOR '(' ')';
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

rbc: TK_PR_RETURN expressao ';';
rbc: TK_PR_CONTINUE ';';
rbc: TK_PR_BREAK ';'

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



