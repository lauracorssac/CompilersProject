#include "AST.h"
#include "LexicalValue.h"
#include <stdio.h>
#include <stdlib.h>

AST* createNode(LexicalValue *value) {  
    AST *newNodePointer = malloc(sizeof(AST));

    AST newNode;
    newNode.child = NULL;
    newNode.sister = NULL;
    newNode.value = value;

    *newNodePointer = newNode;
    return newNodePointer;
}

AST* createNodeNoLexicalValue(NodeType type) {
    
    AST *newNodePointer = malloc(sizeof(AST));

    AST newNode;
    newNode.nodeType = type;
    newNode.value = NULL;
    newNode.child = NULL;
    newNode.sister = NULL;
    
    *newNodePointer = newNode;
    return newNodePointer;
}

void appendChild(AST *rootNode, AST *newChild) {

    AST *firstChild = rootNode->child;
    AST *firstChildPrev = rootNode->child;

    while (firstChild != NULL) {
        firstChildPrev = firstChild;
        firstChild = firstChild->sister;
    }
    if (firstChildPrev != NULL) {
        firstChildPrev->sister = newChild;
    }else {
        rootNode->child = newChild;
    }

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

    if (tree == NULL) { 
        puts("ARVORE NULA VALUES");
        return; 
    }
    
    AST *first_child = tree->child;
    AST *child = tree->child;

    printf("%p [label=\"", tree);
    if (tree->value != NULL) {
        print_literal_value(tree->value->literalTokenValueAndType);
    } else {
        printNodeType(tree->nodeType);
    }
    printf("\"];\n");

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

void printNodeType(NodeType nodeType) {

    switch (nodeType)
    {
        case functionType:
            break;
        case whileType:
            printf("%s", "while");
            break;
        case forType:
            printf("%s","for");
            break;
        case returnType:
            printf("%s","return");
            break;
        case outputType:
            printf("%s","output");
            break;
        case inputType:
            printf("%s","input");
            break;
        default:
            break;
    }

}