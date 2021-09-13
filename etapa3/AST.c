#include "AST.h"
#include "LexicalValue.h"
#include <stdio.h>
#include <stdlib.h>

AST* createNode(LexicalValue value) {  
    AST *newNodePointer = malloc(sizeof(AST));

    AST newNode;
    newNode.child = NULL;
    newNode.sister = NULL;
    newNode.value = value;

    *newNodePointer = newNode;
    return newNodePointer;
}

void printAdresses(AST *tree) {

    if (tree == NULL) { return; }
    
    AST *first_child = tree->child;
    AST *child = tree->child;

    while (child != NULL) {
        printf("%p, %p\n", tree, child);
        child = child->sister;
    }
    while (first_child != NULL)
    {
        printAdresses(first_child);
        first_child = first_child->sister;
    }

}

void printValues(AST *tree) {

    if (tree == NULL) { return; }
    
    AST *first_child = tree->child;
    AST *child = tree->child;

    printf("%p [label=", tree);
    print_literal_value(tree->value.literalTokenValueAndType);
    printf("];\n");

    while (first_child != NULL)
    {
        printValues(first_child);
        first_child = first_child->sister;
    }

}

void exporta(void *arvore) {

    AST *tree_root = (AST *) arvore;
    printAdresses(tree_root);
    printValues(tree_root);

    //printf("%p, %p", print_literal_value(tree->value), print_literal_value(child->value));

}