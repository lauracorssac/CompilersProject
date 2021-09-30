/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef LEXICALVALUE_H
#define LEXICALVALUE_H

typedef union
{
    char * charSequenceValue;
    int integerValue;
    float floatValue;
    int boolValue;
    char charValue;

}LiteralTokenValue;

typedef enum { 
    charSequenceType = 0,
    integerType = 1,
    floatType = 2,
    boolType = 3,
    charType = 4
} LiteralTokenType;

typedef enum { 
    specialCharType = 0,
    composedOperatorType = 1,
    identifierType = 2,
    literalType = 3,
} TokenType;

typedef struct {
    
    LiteralTokenValue value;
    LiteralTokenType type;

} LiteralTokenValueAndType;

typedef struct LexicalValue 
{
    int lineNumber; // da spec: 2.1 (a)
    TokenType tokenType; // da spec: 2.1 (b)
    LiteralTokenValueAndType literalTokenValueAndType; // da spec: 2.1 (c)
    // for non-literal tokens literalTokenValueAndType always assumes:
    // LiteralTokenType: charSequenceType
    // LiteralTokenValue: char * 
    
} LexicalValue;

void print_lexical_value(LexicalValue lexicalValue);
void print_literal_value(LiteralTokenValueAndType literalTokenValueAndType);
LexicalValue* lexicalValueFromLiteralToken(int lineCounter, char *text, LiteralTokenType type);
LexicalValue* lexicalValueFromNonLiteralToken(int lineCounter, char *text, TokenType type);
char *removeFirstAndLast(char *text) ;
void freeLexicalValue(LexicalValue *lexicalValue);

#endif