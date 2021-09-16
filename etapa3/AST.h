/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef AST_H
#define AST_H

#include "LexicalValue.h"

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


typedef struct AST {

    NodeType nodeType;
    LexicalValue *value; 
    struct AST *child;
    struct AST *sister;

} AST;


AST* createNodeNoLexicalValue(NodeType type);
AST* createNode(LexicalValue *value);
void exporta(void *arvore);
void libera(void *arvore);
void printNodeType(NodeType nodeType);
void appendChild(AST *rootNode, AST *newChild);
void prependChild(AST *rootNode, AST *newChild);
AST* createNodeWithLexicalTypeAndValue(NodeType type, LexicalValue *value);

#endif