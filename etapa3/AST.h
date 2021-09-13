#ifndef AST_H
#define AST_H

#include "LexicalValue.h"

typedef enum {

    functionType = 0,
    whileType,
    forType,
    returnType,
    outputType,
    inputType,

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
void printNodeType(NodeType nodeType);
void appendChild(AST *rootNode, AST *newChild);

#endif