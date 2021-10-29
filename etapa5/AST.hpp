/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef AST_HPP
#define AST_HPP

#include "LexicalValue.hpp"
#include "SyntacticalType.hpp"
#include "Code.hpp"
#include <list>
#include <utility>

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
    functionCallType,
    notType,
    subType

} NodeType;

 /* definicao de um nodo da arvore AST */
typedef struct AST {

    SyntacticalType sType; // acrescentando devido E4
    NodeType nodeType;
    InstructionType nodeInstructionType; //only present for operators

    // (optional) value of LexicalValue. 
    // Not NULL for leaves. 
    // Usually NULL for non-leaves. Exceptions are: operators, functions and function calls.
    struct LexicalValue *value; 

    struct AST *child; //(optional) pointer to first child
    struct AST *sister; //(optional) pointer to its parent's next child.

    list<InstructionCode> code;
    CodeOperand resultRegister; //the register where the result is located 
    bool hasPatchworks;

    //this is only present in function call's arguments
    int numberOfParameters;

    //this is only present in function block's commands
    int numberOfReturnStatements;

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
AST* getLastChild(AST *rootNode);


#endif