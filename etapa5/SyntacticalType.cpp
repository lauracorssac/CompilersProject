/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SyntacticalType.hpp"
#include "LexicalValue.hpp"

#include <string.h>

int getSizeForSyntacticalType(SyntacticalType type) {
    switch (type)
    {
    case stringSType:
        return 0;
    case floatSType:
        return 8;
    case intSType:
        return 4;
    case boolSType:
        return 1;
    case charSType:
        return 1;
    case undefinedSType:
        return 0;
    }
    return -1;
}

int getSizeForStringType(char *stringLiteralValue) {
    return strlen(stringLiteralValue);
}