/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYMBOLTABLESTACK_HPP
#define SYMBOLTABLESTACK_HPP

extern "C" {
    #include "SyntacticalType.h"
    #include "LexicalValue.h"
    #include "AST.h"
}

#include "SymbolTable.hpp"
#include "SymbolTableValue.hpp"
#include <list>
#include <string>

using namespace std;
    
typedef struct {

    bool found;
    SymbolTableValue valueFound;

} SearchResult;

class SymbolTableStack {
private:
    // the highest is the "index", the oldest is the scope
    // the global scope always is the last one
    // when a new context is began, a new table is inserted in the front
    // when a context is end, a table is removed from the front
    list<SymbolTable> listOfTables;
    void insertNewItem(string key, SymbolTableValue value);
    list<string> variablesWithPendantTypes;

public:
    SymbolTableStack();
    void beginNewScope();
    SearchResult find(string element);
    void endLastScope();
    
    string stringFromLiteralValue(LiteralTokenValueAndType literalTokenValueAndType);
    int verifyInitializationVariable(LexicalValue *variableLV, int lineNumber);

    int verifyAttribution(string variableKey, string attributionKey, int lineNumber);
    int verifyCoersion(SyntacticalType variableType, SyntacticalType attributionType);
    
    void makeInitialization(AST *variableNode, AST *initializationSymbolNode, AST *initializationValueNode, int lineNumber);

    void insertVectorWithPendantType(int line, int column, LexicalValue *lexicalValue, int indexerValue);
    void insertVariableWithPendantType(int line, int column, LexicalValue *lexicalValue);
    void insertVariableWithType(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType);
    void insertLiteral(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType);
    void updateTypeOfVariablesWithPendantTypes(SyntacticalType type);
    void printItself();
    
    /*
        This function receiver a AST node which contains an lexical value of an identificator
        If the variable was declared, updates the node with the type of the identificator.
        If not, prints signalizes ERR_UNDECLARED error.
    */
    void verifyIdentificatorNode(AST *identificatorNode);


};

#endif