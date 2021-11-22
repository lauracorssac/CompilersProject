
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

// loadI 0 => rX
// storeAI rX => RFP, offsetRetValue 
// loadAI rfp, 0 => rW  
// loadAI rfp, 4 => rY  
// loadAI rfp, 8 => rZ
// store rY => rsp
// store rZ => rfp
// jump => rW

//StoreAI r0 => rsp, 12 // Empilha registrador * quantityOfRegisters
// addI rpc, 7  => r1      
// storeAI r1  => rsp, 0  
// storeAI rsp => rsp, 4  // Salva o rsp (SP)
// storeAI rfp => rsp, 8  // Salva o rfp (RFP)
// 
// storeAI r0 => rsp, 12  // Empilha parâmetro * quantityOfParameters
//
// jumpI => functionLabel            
// loadAI rsp, returnValueOffset => r0 


// LX: nop X = functionLabel
// i2i rsp => rfp 
// addI rsp, rspIncrement => rsp 
// parameters
// loadAI rfp, 12 => r0   
// storeAI r0 => rfp, 20  

typedef enum {

    //instructions for return rp = return procedure  
    rpLoadReturnValueType,
    rpStoreReturnValueType,
    rpLoadReturnAddressType,
    rpLoadRSPType,
    rploadRFPType,
    rpStoreRSPType,
    rpStoreRFPType,
    rpJumpReturnAddressType,

    //instructions for call cp = call procedure
    cpStoreRegisterType,
    cpIncrementRSPType,
    cpDecrementRSPType,
    cpIncrementRPCType,
    cpStoreRPCType,
    cpStoreRSPType,
    cpStoreRFPType,
    cpStoreParameterType,
    cpJumpFunctionType,
    cpLoadReturnValueType,

    //instructions for function prologue fp = function procedure
    fpFunctionNopType,
    fpi2iRSPRFP,
    fpIncrementLocalVariableOffsetRSPType,
    fpLoadParameterType,
    fpStoreParameterType,
    
    attributionStoreType,
    loadIdentifierType, 

    stackInitialization,

    //instructions for bool flow bf = bool flow
    // bfLoadZero,
    bfCompareNE,
    // bfCBR

    functionEnd

} InstructionCodeType;

typedef struct {
    
    // as struct is optional, we need this to see if it was initialized
    bool notEmpty;

    // name of global variable or function
    string name; 
    
    //some instructions contain AST type
    InstructionCodeType instructionCodeType; 

    //for local variables, the offset from rbp
    //for global, the offset from rbss
    int offset;

} InstructionAdditionalDetails;

#endif