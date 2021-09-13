#ifndef AST_H
#define AST_H

#include "LexicalValue.h"

typedef struct AST {

    LexicalValue value; 
    struct AST *child;
    struct AST *sister;

} AST;


AST* createNode(LexicalValue value);
void exporta(void *arvore);

#endif