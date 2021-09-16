/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

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
    newNode.nodeType = noType;

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

AST* createNodeWithLexicalTypeAndValue(NodeType type, LexicalValue *value) {
    
    AST *newNodePointer = malloc(sizeof(AST));

    AST newNode;
    newNode.nodeType = type;
    newNode.value = value;
    newNode.child = NULL;
    newNode.sister = NULL;
    
    *newNodePointer = newNode;
    return newNodePointer;
}


void appendChild(AST *rootNode, AST *newChild) {

    if (rootNode == NULL) { return; }

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

void prependChild(AST *rootNode, AST *newChild) {

    if (rootNode == NULL) { return; }

    AST *firstChild = rootNode->child;
    
    newChild->sister = firstChild;
    rootNode->child = newChild;

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

    if (tree->nodeType != noType) {
        printNodeType(tree->nodeType);
    }
    if (tree->value != NULL) {
        
        print_literal_value(tree->value->literalTokenValueAndType);
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
        case ifType:
            printf("%s","if");
            break;
        case returnType:
            printf("%s","return");
            break;
        case breakType:
            printf("%s","break");
            break;
        case continueType:
            printf("%s","continue");
            break;
        case outputType:
            printf("%s","output");
            break;
        case inputType:
            printf("%s","input");
            break;
        case ternaryType:
            printf("%s","?:");
            break;
        case indexerType:
            printf("%s","[]");
            break;
        case attributionType:
            printf("%s","=");
            break;
        case initializerType:
            printf("%s","<=");
            break;
        case functionCallType:
            printf("call ");
            break;
        default:
            break;
    }

}