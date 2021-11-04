/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

%{

#include "LexicalValue.hpp"
extern "C"
{ 
    int yylex(void);
    int yylex_destroy(void);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "parser.tab.h"
#include "AST.hpp"
int line_counter = 1;
%}

%x multiLineComment
NEWLINE "\n"
CLOSECOMMENT "*/"
BEGINCOMMENT "/*"
DIGIT [0-9]
INTEGER {DIGIT}+

%%

 /*    special characters    */

[\,\;\:\(\)\[\]\{\}\.] {
    return yytext[0]; 
}

[\=\$\+\-\*\/\%\^\&\|\<\>\!\?\#] { 
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, specialCharType);
    return yytext[0]; 
}

 /*    reserved words    */

"int" {return TK_PR_INT;}
"float" {return TK_PR_FLOAT;}
"bool" {return TK_PR_BOOL;}
"char" {return TK_PR_CHAR;}
"string" {return TK_PR_STRING;}
"if" {return TK_PR_IF;}
"then" {return TK_PR_THEN;}
"else" {return TK_PR_ELSE;}
"while" {return TK_PR_WHILE;}
"do" {return TK_PR_DO;}
"input" {return TK_PR_INPUT;}
"output" {return TK_PR_OUTPUT;}
"return" {return TK_PR_RETURN;}
"const" {return TK_PR_CONST;}
"static" {return TK_PR_STATIC;}
"foreach" {return TK_PR_FOREACH;}
"for" {return TK_PR_FOR;}
"switch" {return TK_PR_SWITCH;}
"case" {return TK_PR_CASE;}
"break" {return TK_PR_BREAK;}
"continue" {return TK_PR_CONTINUE;}
"class" {return TK_PR_CLASS;}
"private" {return TK_PR_PRIVATE;}
"public" {return TK_PR_PUBLIC;}
"protected" {return TK_PR_PROTECTED;}
"end" {return TK_PR_END;}
"default" {return TK_PR_DEFAULT;}

 /*    operators    */

"<=" {
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, composedOperatorType);
    return TK_OC_LE;
}
">=" {
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, composedOperatorType);
    return TK_OC_GE;
}
"==" {
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, composedOperatorType);
    return TK_OC_EQ;
}
"!=" {
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, composedOperatorType);
    return TK_OC_NE;
}
"&&" {
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, composedOperatorType);
    return TK_OC_AND;
}
"||" {
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, composedOperatorType);
    return TK_OC_OR;
}
">>" {
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, composedOperatorType);
    return TK_OC_SL;
}
"<<" {
    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, composedOperatorType);
    return TK_OC_SR;
}

 /*    literals    */

{INTEGER} {
    yylval.lexicalValue = lexicalValueFromLiteralToken(line_counter, yytext, integerType);
    return TK_LIT_INT;
}

{INTEGER}"."{DIGIT}+([eE][-+]?{DIGIT}+)? {
    yylval.lexicalValue = lexicalValueFromLiteralToken(line_counter, yytext, floatType);
    return TK_LIT_FLOAT;
}

"false" {
    yylval.lexicalValue = lexicalValueFromLiteralToken(line_counter, yytext, boolType);
    return TK_LIT_FALSE;
}

"true" {
    yylval.lexicalValue = lexicalValueFromLiteralToken(line_counter, yytext, boolType);
    return TK_LIT_TRUE;
}

 /* char: allows all characters but the new line and ' */
\'[^'\n]\' {
    yylval.lexicalValue = lexicalValueFromLiteralToken(line_counter, yytext, charType);
    return TK_LIT_CHAR;
} 
 
 /* string: allows all chars but new line and " */
\"[^"\n]+\" { 
    yylval.lexicalValue = lexicalValueFromLiteralToken(line_counter, yytext, charSequenceType);
    return TK_LIT_STRING;
}

 /*    identifiers    */

[A-Za-z_][0-9A-Za-z_]* {

    yylval.lexicalValue = lexicalValueFromNonLiteralToken(line_counter, yytext, identifierType);
    return TK_IDENTIFICADOR;
}

 /*    line counting    */

<INITIAL,multiLineComment>{NEWLINE} { line_counter++; }

 /*    ignore space and tabs  */

[\t ] { }

 /*    comments    */

"//".* { } /* allows all chars in the single-line comments */

{BEGINCOMMENT} BEGIN(multiLineComment);

<multiLineComment>[^*\n]* { } /* allows everything that's not a * */
<multiLineComment>"*"+[^/\n]* { } /* allows all * not followed by '/'s */

<multiLineComment>{CLOSECOMMENT} {
    BEGIN(INITIAL);
}

 /*    erros    */

. { return TOKEN_ERRO; } /* all that was not recognized is an error */

%%

int get_line_number (void) {
    return line_counter;
}
