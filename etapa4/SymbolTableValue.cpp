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
extern SyntacticalType lastDeclaredType;
using namespace std;

void printValue(SymbolTableValue symbolTableValue) {

    cout << endl;
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
    //print_lexical_value(*symbolTableValue.lexicalValue);
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
        break;
    }
}

SymbolTableValue createVariableWithLastDeclaredType(int line, int column, LexicalValue *lexicalValue) {

    SymbolTableValue value = {.type: lastDeclaredType, .line: line, .column: column, 
    .lexicalValue: lexicalValue, .kind: variableKind, 
    .size: getSizeForSyntacticalType(lastDeclaredType)}
    return value;
}

SymbolTableValue createVariableWithInitialization(int line, int column, SyntacticalType type, 
LexicalValue *lexicalValueIdentifier, 
LexicalValue *lexicalValueInitialization) {

    int size;
    if (type == stringSType) {
        size = getSizeForStringType(lexicalValueInitialization->literalTokenValueAndType.value.charSequenceValue);
    } else  {
        size = getSizeForSyntacticalType(lastDeclaredType);
    }

    SymbolTableValue value = { .type: type, .line: line, .column: column, 
    .lexicalValue: lexicalValueIdentifier, .kind: variableKind, .size: size };
    return value;
}

SymbolTableValue createVectorWithLastDeclaredType(int line, int column, 
LexicalValue *lexicalValue, int indexerValue) {
    
    SymbolTableValue value = { .type: lastDeclaredType, .line: line, .column: column, 
    .lexicalValue: lexicalValue, .kind: vectorKind, 
    .size: getSizeForSyntacticalType(lastDeclaredType) * indexerValue }
    return value;
}