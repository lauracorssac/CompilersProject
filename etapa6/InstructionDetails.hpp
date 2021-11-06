
/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <string>
//#include "AST.hpp"

using namespace std;

 /* definicao dos tipos de nodos existentes.
    noType é usado geralmente quando há um valor léxico no nodo, como literais, identificadores, 
    operadores,..
  */
typedef enum {

    noType = 0,
    identifierNodeType,
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

typedef enum {

    nop = 0,
    add = 1,
    sub,
    mult,
    _div,
    addI,
    subI,
    rsubI,
    multI,
    divI,
    rdivI,
    lshift,
    lshiftI,
    rshift,
    rshiftI,
    _and,
    andI,
    _or,
    orI,
    _xor,
    xorI,
    load, 
    loadI, 
    loadAI, 
    loadAO, 
    cload,
    cloadAI,
    cloadAO,
    store, 
    storeAI, 
    storeAO, 
    cstore, 
    cstoreAI, 
    cstoreAO, 
    i2i,
    c2c,
    c2i,
    i2c,
    jump,
    jumpI,
    cbr,
    cmp_LT,
    cmp_LE,
    cmp_EQ,
    cmp_GE,
    cmp_GT,
    cmp_NE,
    halt,
} InstructionType;

typedef struct {
    
    // as struct is optional, we need this to see if it was initialized
    bool notEmpty;

    // name of global variable or function
    string name; 
    
    //some instructions contain AST type
    NodeType nodeType; 

} InstructionAdditionalDetails;

#endif