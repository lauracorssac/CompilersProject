/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "Utils.hpp"
#include <string>

extern "C" {
    #include "LexicalValue.h"
}

using namespace std;

string stringFromLiteralValue(LiteralTokenValueAndType literalTokenValueAndType) {
    
    LiteralTokenType litTokenType = literalTokenValueAndType.type;
    
    if (litTokenType == charSequenceType) {
        return string(literalTokenValueAndType.value.charSequenceValue);
    } else if (litTokenType == integerType) {
        return to_string(literalTokenValueAndType.value.integerValue);
    } else if (litTokenType == floatType) {
        return to_string(literalTokenValueAndType.value.floatValue);
    } else if (litTokenType == boolType) {
        return to_string(literalTokenValueAndType.value.boolValue);
    } else if (litTokenType == charType) {
        string convertedString(1, literalTokenValueAndType.value.charValue);
        return convertedString;
    } 
    return "";
}

void copyStringToCharPointer(string string, char *charBuffer) {
    int size = string.size();
    charBuffer = new char[size + 1];
    bzero(charBuffer, size +1);
    strncpy(charBuffer, string.c_str(), size);
}