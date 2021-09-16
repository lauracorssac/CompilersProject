/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LexicalValue.h"

void print_lexical_value(LexicalValue lexicalValue) {

    printf("Line number = %d\n", lexicalValue.lineNumber);
    printf("Token Type = %d\n", lexicalValue.tokenType);
    
    LiteralTokenType litTokenType = lexicalValue.literalTokenValueAndType.type;
    printf("Literal Token Type = %d\n", litTokenType);

    printf("LiteralTokenValue = ");

    print_literal_value(lexicalValue.literalTokenValueAndType);
    printf("\n");
}

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
        litValue.charValue = strdup(text)[1];
        break;
    default:
        break;
    }
    LiteralTokenType litType = type;
    LiteralTokenValueAndType literalTokenValueAndType = { litValue, litType };
    TokenType tokenType = literalType;
    LexicalValue lexicalValue = { lineCounter, tokenType, literalTokenValueAndType };
    
    LexicalValue *valor_lexico = malloc(sizeof(LexicalValue)); 
    *valor_lexico = lexicalValue;
    return valor_lexico;

}

LexicalValue* lexicalValueFromNonLiteralToken(int lineCounter, char *text, TokenType type) {

    LiteralTokenValue litValue;
    litValue.charSequenceValue = strdup(text);

    LiteralTokenType litType = charSequenceType;
    LiteralTokenValueAndType literalTokenValueAndType = { litValue, litType };
    
    TokenType tokenType = type;
    LexicalValue lexicalValue = { lineCounter, tokenType, literalTokenValueAndType };
    
    LexicalValue *valor_lexico = malloc(sizeof(LexicalValue)); 
    *valor_lexico = lexicalValue;
    return valor_lexico;

}

char *removeFirstAndLast(char *text) {
    char *mystr = text;
    mystr++; /* removing first item */
    mystr[strlen(mystr) - 1] = '\0';  /* removing last item */
    return mystr;
}