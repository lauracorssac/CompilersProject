/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef RELEASEMANAGER_HPP
#define RELEASEMANAGER_HPP

#include "AST.hpp"
#include <list>

using namespace std;

typedef struct DeletionHelp{
  struct AST *nodeRef;
  struct DeletionHelp *next;
} DeletionHelp;

class ReleaseManager {

private:
/* list used to store all the AST nodes created */
  list<AST *> releasePool;
public:
ReleaseManager();
/* called in the shutdown routine, this method frees release pool */
void freeReleasePool();
/* called every time a node is created, inserts a new object in the pool */
void insertNewNode(AST *newNode);

};
 
#endif