/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "SymbolTableValue.hpp"
#include <string>
#include <iostream>
#include <list>

extern "C" {
    #include "LexicalValue.h"
    #include "SyntacticalType.h"
}
using namespace std;

void printValue(SymbolTableValue symbolTableValue) {

    cout << " ---- Printing symbol table value -----" << endl;
    cout << "Line: " << symbolTableValue.line << endl;
    cout << "Column: " << symbolTableValue.column << endl;
    cout << "Kind: ";
    printKind(symbolTableValue.kind);
    cout << endl;
    cout << "Size: " << to_string(symbolTableValue.size) << endl;
    cout << "Type: ";
    printSyntacticalType(symbolTableValue.type);
    cout << endl;
    cout << "List of Parameters:" << endl;
    printListOfParameters(symbolTableValue.listOfParameters);
    cout << "Lexical Value: ";
    print_lexical_value(*(symbolTableValue.lexicalValue));
    cout << endl;

}

void printListOfParameters(list<Parameter> listOfParameters) {
    list<Parameter>::iterator it;
    for (it = listOfParameters.begin(); it != listOfParameters.end(); ++it) {
        cout << "Parameter: ";
        printSyntacticalType(it->type);
        cout << endl;
    }
}

void printKind(Kind kind) {
     switch (kind)
    {
    case literalKind:
        cout << "Literal";
        break;
    case variableKind:
        cout << "Variable";
        break;
    case functionKind:
        cout << "Function";
        break;
    case vectorKind:
        cout << "Vector";
        break;
    default:
        cout << "No Kind";
        break;
    }
}

void printSyntacticalType(SyntacticalType sType) {
    switch (sType)
    {
    case stringSType:
        cout << "string";
        break;
    case charSType:
        cout << "char";
        break;
    case boolSType:
        cout << "bool";
        break;
    case floatSType:
        cout << "float";
        break;
    case intSType:
        cout << "integer";
        break;
    default:
        cout << "undefined";
        break;
    }
}



SymbolTableValue createLiteral(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {

    int size;
     if (sType == stringSType) {
        size = getSizeForStringType(lexicalValue->literalTokenValueAndType.value.charSequenceValue);
    } else  {
        size =getSizeForSyntacticalType(sType);
    }

    SymbolTableValue value = {.line= line, .column= column, .kind= literalKind, .type= sType,
    .size= size, .lexicalValue= lexicalValue};
    return value;
}

SymbolTableValue createVariableWithPendantType(int line, int column, LexicalValue *lexicalValue) {

    SymbolTableValue value = {.line= line, .column= column, .kind= variableKind, .type= undefinedSType,
    .size= 0, .lexicalValue= lexicalValue };
    return value;
}

SymbolTableValue createFunctionWithTypeNoParameters(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {

    SymbolTableValue value = {.line= line, .column= column, .kind= functionKind, .type= sType,
    .size= getSizeForSyntacticalType(sType), .lexicalValue= lexicalValue };
    return value;
}

SymbolTableValue createVariableWithType(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType) {

    SymbolTableValue value = {.line= line, .column= column, .kind= variableKind, .type= sType,
    .size= getSizeForSyntacticalType(sType), .lexicalValue= lexicalValue };
    return value;
}

SymbolTableValue createVariableWithInitialization(int line, int column, SyntacticalType type, 
LexicalValue *lexicalValueIdentifier, 
LexicalValue *lexicalValueInitialization) {

    int size;
    if (type == stringSType) {
        size = getSizeForStringType(lexicalValueInitialization->literalTokenValueAndType.value.charSequenceValue);
    } else  {
        size = getSizeForSyntacticalType(type);
    }

    SymbolTableValue value = { .line= line, .column= column, .kind= variableKind, .type= type, .size= size,  
    .lexicalValue= lexicalValueIdentifier};
    return value;
}

SymbolTableValue createVectorWithPendantType(int line, int column, 
LexicalValue *lexicalValue, int indexerValue) {
    
    SymbolTableValue value = { .line= line, .column= column,  .kind= vectorKind, .type= undefinedSType, 
    .size= indexerValue, .lexicalValue= lexicalValue };
    return value;
}