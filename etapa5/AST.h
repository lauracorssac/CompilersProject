/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef AST_H
#define AST_H

#include "LexicalValue.h"
#include "SyntacticalType.h"

 /* definicao dos tipos de nodos existentes.
    noType é usado geralmente quando há um valor léxico no nodo, como literais, identificadores, 
    operadores,..
  */
typedef enum {

    noType = 0,
    functionType,
    whileType,
    forType,
    ifType,
    returnType,
    breakType,
    continueType,
    outputType,
    inputType,
    indexerType,
    attributionType,
    initializerType,
    ternaryType,
    functionCallType

} NodeType;

 /* definicao de um nodo da arvore AST */
typedef struct AST {

    SyntacticalType sType; // acrescentando devido E4
    NodeType nodeType;

    // (optional) value of LexicalValue. 
    // Not NULL for leaves. 
    // Usually NULL for non-leaves. Exceptions are: operators, functions and function calls.
    LexicalValue *value; 

    struct AST *child; //(optional) pointer to first child
    struct AST *sister; //(optional) pointer to its parent's next child.

    struct Code *code;

} AST;


AST* createNodeNoLexicalValue(NodeType type);
AST* createNodeNoType(LexicalValue *value);
AST* createNodeNoTypeWithSType(LexicalValue *value, SyntacticalType sType);
AST* createNodeWithLexicalTypeAndValue(NodeType type, LexicalValue *value);

void exporta(void *arvore);
void libera(void *arvore);

void printNodeType(NodeType nodeType);
void appendChild(AST *rootNode, AST *newChild);
void prependChild(AST *rootNode, AST *newChild);


#endif