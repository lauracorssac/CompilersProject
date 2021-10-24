/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYMBOLTABLEVALUE_HPP
#define SYMBOLTABLEVALUE_HPP

#include <string>
#include <list>

using namespace std;

#include "SyntacticalType.hpp"
#include "LexicalValue.hpp"
#include "Code.hpp"
extern "C" {
   
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
    OffsetAndScope variableScope; //deslocamento em relação a rbss ou rfp
    int functionLabel; //label da função. main é sempre L0. 
    int sizeOfParameters; //o total de espaço ocupado por todos os parametros da funcao

} SymbolTableValue;

void printValue(SymbolTableValue symbolTableValue);
void printKind(Kind kind);
void printListOfParameters(list<Parameter> listOfParameters);
void printSyntacticalType(SyntacticalType sType);
SymbolTableValue createVariableWithPendantType(int line, int column, LexicalValue *lexicalValue, OffsetAndScope scope);
SymbolTableValue createFunctionWithTypeNoParameters(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType, int label);
SymbolTableValue createVariableWithType(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType, OffsetAndScope scope);
SymbolTableValue createVariableWithInitialization(int line, int column, SyntacticalType type, 
LexicalValue *lexicalValueIdentifier, 
LexicalValue *lexicalValueInitialization);
SymbolTableValue createLiteral(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType);
SymbolTableValue createVectorWithPendantType(int line, int column, LexicalValue *lexicalValue, int indexerValue);

#endif