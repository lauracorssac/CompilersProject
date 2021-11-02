/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "Utils.hpp"
#include <string>
#include <cstring>


#include "LexicalValue.hpp"
extern "C" {
   
}

using namespace std;

int integerFromLiteralValue(LiteralTokenValueAndType literalTokenValueAndType) {
    
    LiteralTokenType litTokenType = literalTokenValueAndType.type;
    
    if (litTokenType == charSequenceType) {
        return 0;
    } else if (litTokenType == integerType) {
        return literalTokenValueAndType.value.integerValue;
    } else if (litTokenType == floatType) {
        return 0;
    } else if (litTokenType == boolType) {
        return literalTokenValueAndType.value.boolValue;
    } else if (litTokenType == charType) {
        return (int)(literalTokenValueAndType.value.charValue); 
    } 
    return -1;
}


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
