/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#ifndef RELEASEPOOL_H
#define RELEASEPOOL_H

#include "AST.h"

typedef struct DeletionHelp{
  AST *nodeRef;
  struct DeletionHelp *next;
} DeletionHelp;
 
 /* called in the shutdown routine, this method frees release pool */
void freeReleasePool();
 /* called every time a node is created, inserts a new object in the pool */
void insertNewNode(AST *newNode);

#endif