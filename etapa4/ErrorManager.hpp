/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef ERRORMANAGER_HPP
#define ERRORMANAGER_HPP

#include "SymbolTableValue.hpp"
#include <string>
using namespace std;

class ErrorManager {
public:
    static void printStringVector(string variableKey);
    static void printDeclaredVariableInitialization(string variableKey, SymbolTableValue valueFound, int line);
    static void printAttributionError(string variableKey, string attributionKey, int line);
    static void printElementsNotFoundAttribution(string variableKey, string attributionKey, int line);
    static void printElementNotFoundAttribution(string variableKey, string attributionKey, string undeclared, int line);
    static void printStringToXAttribution(string variableKey, string attributionKey, SyntacticalType variableType, int line);
    static void printCharToXAttribution(string variableKey, string attributionKey, SyntacticalType variableType, int line);
    static void printFunctionAttribution(string variableKey, string attributionKey, int line);
    static void printVectorAttribution(string variableKey, string attributionKey, int line);
    static void printWrongTypeAttribution(string variableKey, string attributionKey, SyntacticalType variableType, SyntacticalType attributionType, int line);
   // static void printMaxStringAttribution(string variableKey, SymbolTableValue variableValue, int line);
};

#endif