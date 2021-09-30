/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <unordered_map>
#include <string>

using namespace std;

class Table {
    public:
    unordered_map<string, string> symbolTable;
    Table();
};


#endif