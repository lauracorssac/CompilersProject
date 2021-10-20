/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef CODE_HPP
#define CODE_HPP
#include <list>

using namespace std;

typedef enum {

    rfp =0,
    rsp,
    rbss

} RegisterPointerType;

typedef enum {

    global =0,
    local
    

} VariableScope;

typedef struct {

    VariableScope scope;
    int offset;

} OffsetAndScope;

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

typedef enum {

    //register is a reseved word, thats why the _
    _register = 0, 
    registerPointer,
    label,
    number 

} CodeOperandType;

/* an operand of an ILOC instruction */
typedef struct {

    CodeOperandType operandType;
    int numericalValue;

} CodeOperand;

typedef struct {

    int prefixLabel;
    InstructionType instructionType;
    /* list of operands in the left side of the arrow */
    list<CodeOperand> leftOperands;
    /* list of operands in the right side of the arrow */
    list<CodeOperand> rightOperands;
  
} InstructionCode;



#endif