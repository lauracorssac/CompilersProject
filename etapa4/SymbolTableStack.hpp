/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYMBOLTABLESTACK_HPP
#define SYMBOLTABLESTACK_HPP

extern "C" {
    #include "SyntacticalType.h"
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

public:
    SymbolTableStack();
    void beginNewScope();
    SearchResult find(string element);
    void endLastScope();
    
    int verifyAttribution(string variableKey, string attributionKey, int lineNumber);
    int verifyCoersion(SyntacticalType variableType, SyntacticalType attributionType);
    void insertVariableWithLastDeclaredType(int line, int column, LexicalValue *lexicalValue, int indexerValue);


};

#endif