/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "LexicalValue.hpp"

using namespace std;

int integerFromLiteralValue(LiteralTokenValueAndType literalTokenValueAndType);
string stringFromLiteralValue(LiteralTokenValueAndType literalTokenValueAndType);
void copyStringToCharPointer(string string, char *charBuffer);

#endif