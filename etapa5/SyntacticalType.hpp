/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYNTACTICALTYPE_HPP
#define SYNTACTICALTYPE_HPP

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