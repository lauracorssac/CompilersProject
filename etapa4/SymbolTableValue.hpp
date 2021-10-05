/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYMBOLTABLEVALUE_HPP
#define SYMBOLTABLEVALUE_HPP

#include <string>
#include <list>

using namespace std;

extern "C" {
    #include "SyntacticalType.h"
    #include "LexicalValue.h"
}

// Natureza
typedef enum {
    literalKind = 1,
    variableKind,
    functionKind,
    vectorKind,
} Kind;

typedef struct {

    SyntacticalType type;
    
} Parameter;

typedef struct {

    int line; //spec: E4 2.1 a
    int column; //spec: E4 2.1 a
    Kind kind; //spec: E4 2.1 b
    SyntacticalType type; //spec: E4 2.1 c 
    int size; //spec: E4 2.1 d
    list<Parameter> listOfParameters; //spec: E4 2.1 e
    LexicalValue *lexicalValue; //spec E4 2.1 f

} SymbolTableValue;

void printValue(SymbolTableValue symbolTableValue);
void printKind(Kind kind);
void printListOfParameters(list<Parameter> listOfParameters);
void printSyntacticalType(SyntacticalType sType);
SymbolTableValue createVariableWithPendantType(int line, int column, LexicalValue *lexicalValue);
SymbolTableValue createVariableWithInitialization(int line, int column, SyntacticalType type, 
LexicalValue *lexicalValueIdentifier, 
LexicalValue *lexicalValueInitialization);
SymbolTableValue createVectorWithPendantType(int line, int column, LexicalValue *lexicalValue, int indexerValue);

#endif