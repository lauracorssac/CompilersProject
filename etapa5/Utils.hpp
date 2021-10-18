/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

extern "C" {
    #include "LexicalValue.h"
}

using namespace std;

string stringFromLiteralValue(LiteralTokenValueAndType literalTokenValueAndType);
void copyStringToCharPointer(string string, char *charBuffer);

#endif