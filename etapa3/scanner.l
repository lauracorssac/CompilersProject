%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "parser.tab.h"
#include "LexicalValue.h"
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

"," {return (int)',';} 
";" {return (int)';';}
":" {return (int)':';}
"(" {return (int)'(';}
")" {return (int)')';}
"[" {return (int)'[';}
"]" {return (int)']';}
"{" {return (int)'{';}
"}" {return (int)'}';}
"+" {return (int)'+';}
"-" {return (int)'-';}
"|" {return (int)'|';}
"*" {return (int)'*';}
"/" {return (int)'/';}
"<" {return (int)'<';}
">" {return (int)'>';}
"=" {return (int)'=';}
"!" {return (int)'!';}
"&" {return (int)'&';}
"%" {return (int)'%';}
"#" {return (int)'#';}
"^" {return (int)'^';}
"." {return (int)'.';}
"$" {return (int)'$';}
"?" {return (int)'?';}

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

"<=" {return TK_OC_LE;}
">=" {return TK_OC_GE;}
"==" {return TK_OC_EQ;}
"!=" {return TK_OC_NE;}
"&&" {return TK_OC_AND;}
"||" {return TK_OC_OR;}
">>" {return TK_OC_SL;}
"<<" {return TK_OC_SR;}

 /*    literals    */

{INTEGER} {return TK_LIT_INT;}
{INTEGER}"."{DIGIT}+([eE][-+]?{DIGIT}+)? {return TK_LIT_FLOAT;}

"false" {return TK_LIT_FALSE;}
"true" {return TK_LIT_TRUE;}

\'[^'\n]\' {return TK_LIT_CHAR;} /* allows all characters but the new line and ' */
 /* allows all chars but new line and " */
\"[^"\n]+\" { 
    char *mystr = strdup(yytext);
    mystr++; /* removing first item */
    mystr[strlen(mystr) - 1] = '\0';  /* removing last item */
    puts(mystr);

    LiteralTokenType litType = charSequenceType;
    LiteralTokenValue litValue;
    litValue.charSequenceValue = mystr;
    LiteralTokenValueAndType literalTokenValueAndType = { litValue, litType };
    TokenType tokenType = literalType;
    LexicalValue lexicalValue = { line_counter, tokenType, literalTokenValueAndType };
    
    LexicalValue *valor_lexico = malloc(sizeof(LexicalValue)); 
    *valor_lexico = lexicalValue;
    yylval.lexicalValue = valor_lexico;
    return TK_LIT_STRING;
}

 /*    identifiers    */

[A-Za-z_][0-9A-Za-z_]* {return TK_IDENTIFICADOR;}

 /*    line counting    */

<INITIAL,multiLineComment>{NEWLINE} { line_counter++; }

 /*    ignore space    */

" " { }

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
