/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LexicalValue.h"

/* funcao usada para debug */
void print_lexical_value(LexicalValue lexicalValue) {

    printf("Line number = %d\n", lexicalValue.lineNumber);
    printf("Token Type = %d\n", lexicalValue.tokenType);
    
    LiteralTokenType litTokenType = lexicalValue.literalTokenValueAndType.type;
    printf("Literal Token Type = %d\n", litTokenType);

    printf("LiteralTokenValue = ");

    print_literal_value(lexicalValue.literalTokenValueAndType);
    printf("\n");
}

/* funcao usada para printar o valor literal */
void print_literal_value(LiteralTokenValueAndType literalTokenValueAndType) {
    
    LiteralTokenType litTokenType = literalTokenValueAndType.type;
    
    if (litTokenType == charSequenceType) {
        printf("%s", literalTokenValueAndType.value.charSequenceValue);
    } else if (litTokenType == integerType) {
        printf("%d", literalTokenValueAndType.value.integerValue);
    } else if (litTokenType == floatType) {
        printf("%f", literalTokenValueAndType.value.floatValue);
    } else if (litTokenType == boolType) {
        printf("%d", literalTokenValueAndType.value.boolValue);
    } else if (litTokenType == charType) {
        printf("%c", literalTokenValueAndType.value.charValue);
    } 

}

 /* cria um valor lexico a partir de um token literal */
LexicalValue* lexicalValueFromLiteralToken(int lineCounter, char *text, LiteralTokenType type) {
    
    LiteralTokenValue litValue;
    switch (type)
    {
    case charSequenceType:
        litValue.charSequenceValue = strdup(removeFirstAndLast(text));
        break;
    case integerType:
        litValue.integerValue = atoi(text);
        break;
    case floatType:
        litValue.floatValue = atof(text);
        break;
    case boolType:
        litValue.boolValue = (strncmp (text,"true",4) == 1);
        break;
    case charType:
        strncpy(&litValue.charValue, removeFirstAndLast(text), 1);
        break;
    default:
        break;
    }
    LiteralTokenType litType = type;
    LiteralTokenValueAndType literalTokenValueAndType = { litValue, litType };
    TokenType tokenType = literalType;
    LexicalValue lexicalValue = { lineCounter, tokenType, literalTokenValueAndType };
    
    LexicalValue *valor_lexico = malloc(sizeof(lexicalValue)); 
    *valor_lexico = lexicalValue;
    return valor_lexico;

}

 /* cria um valor lexico a partir de um token nao literal
    Exemplos: caracteres especiais, operadores compostos e identificadores
  */
LexicalValue* lexicalValueFromNonLiteralToken(int lineCounter, char *text, TokenType type) {

    LiteralTokenValue litValue;
    litValue.charSequenceValue = strdup(text);

    LiteralTokenType litType = charSequenceType;
    LiteralTokenValueAndType literalTokenValueAndType = { litValue, litType };
    
    TokenType tokenType = type;
    LexicalValue lexicalValue = { lineCounter, tokenType, literalTokenValueAndType };
    
    LexicalValue *valor_lexico = malloc(sizeof(lexicalValue)); 
    *valor_lexico = lexicalValue;
    return valor_lexico;

}

 /* remove valor lexico. Caso tenha uma string armazenada, remove ela também. */
void freeLexicalValue(LexicalValue *lexicalValue) {

    if (lexicalValue == NULL) { return; }

    if (lexicalValue->literalTokenValueAndType.type == charSequenceType) {
        free(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    }

    free(lexicalValue);

}

 /* remove primeiro e ultimo caracter */
char *removeFirstAndLast(char *text) {
    char *mystr = text;
    mystr++; /* removing first item */
    mystr[strlen(mystr) - 1] = '\0';  /* removing last item */
    return mystr;
}