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

DeletionHelp *releasePool;
void freeReleasePool();
void insertNewNode(AST *newNode);

#endif