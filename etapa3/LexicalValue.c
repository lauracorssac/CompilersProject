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

    if (litTokenType == charSequenceType) {
        puts(lexicalValue.literalTokenValueAndType.value.charSequenceValue);
    } else if (litTokenType == integerType) {
        printf("%d\n", lexicalValue.literalTokenValueAndType.value.integerValue);
    } else if (litTokenType == floatType) {
        printf("%f\n", lexicalValue.literalTokenValueAndType.value.floatValue);
    } else if (litTokenType == boolType) {
        printf("%d\n", lexicalValue.literalTokenValueAndType.value.boolValue);
    } else if (litTokenType == charType) {
         printf("%c\n", lexicalValue.literalTokenValueAndType.value.charValue);
    } 

}