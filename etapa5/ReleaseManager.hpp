/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef RELEASEMANAGER_HPP
#define RELEASEMANAGER_HPP

#include "AST.hpp"

typedef struct DeletionHelp{
  struct AST *nodeRef;
  struct DeletionHelp *next;
} DeletionHelp;

class ReleaseManager {

private:
/* list used to store all the AST nodes created */
  DeletionHelp *releasePool;
public:
ReleaseManager();
/* called in the shutdown routine, this method frees release pool */
void freeReleasePool();
/* called every time a node is created, inserts a new object in the pool */
void insertNewNode(AST *newNode);

};
 
#endif