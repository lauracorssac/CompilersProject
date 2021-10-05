/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYNTACTICALTYPE_H
#define SYNTACTICALTYPE_H

typedef enum SyntacticalType {
    stringSType = 0,
    floatSType,
    intSType,
    boolSType,
    charSType,
    undefinedSType,
} SyntacticalType;

int getSizeForSyntacticalType(SyntacticalType type);
int getSizeForStringType(char *stringLiteralValue);

#endif