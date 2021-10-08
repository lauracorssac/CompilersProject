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
    string lastDeclaredFunction;
    list<Parameter> pendantParameters;

public:
    SymbolTableStack();
    void beginNewScope();
    SearchResult find(string element);
    void endLastScope();
    
    int verifyCoersion(SyntacticalType variableType, SyntacticalType attributionType);
    
    void makeReturn(AST *returnSymbolNode, AST *returnExpressionNode);
    void verifyVectorNode(AST *identificatorNode, AST *indexerSymbolNode, AST *indexerNode);
    void makeAttributionVector(AST *variableNode, AST *attributionSymbolNode, AST *attributionNode, 
    AST *indexerSymbolNode, AST *indexerNode, int lineNumber);
    void makeAttributionVariable(AST *variableNode, AST *attributionSymbolNode, AST *attributionNode);
    void makeInitialization(AST *variableNode, AST *initializationSymbolNode, AST *initializationValueNode);
    void makeFunctionCall(AST *identificatorNode, AST *parametersNode);
    void makeInput(AST *inputNode, AST *identifierNode);
    void makeOutputIdentifier(AST *outputNode, AST *identifierNode);
    void makeOutputLiteral(AST *outputNode, AST *literalNode);
    void makeShift(AST *shiftSumbolNode, AST *shiftLiteralNode);
    void insertParameterWithType(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType);
    void insertVectorWithPendantType(int line, int column, LexicalValue *lexicalValue, int indexerValue);
    void insertVariableWithPendantType(int line, int column, LexicalValue *lexicalValue);
    void insertVariableWithType(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType);
    void insertFunction(int line, int column, AST *identificatorNode, SyntacticalType sType);
    void insertLiteral(int line, int column, LexicalValue *lexicalValue, SyntacticalType sType);
    void updateTypeOfVariablesWithPendantTypes(SyntacticalType type);
    void printItself();
    void updateFunctionWithPendantParameters();
    void makeBinaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node);
    void makeUnaryOperation(AST *exp1Node, AST *operandNode);
    void makeTernaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node, AST *exp3Node);
    SyntacticalType getInferenceBinaryOperation(SyntacticalType type1, SyntacticalType type2);
    
    /*
        This function receiver a AST node which contains an lexical value of an identificator
        If the variable was declared, updates the node with the type of the identificator.
        If not, prints signalizes ERR_UNDECLARED error.
    */
    void verifyIdentificatorNode(AST *identificatorNode);


};

#endif