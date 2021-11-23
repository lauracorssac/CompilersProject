/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "ReleaseManager.h"
#include <stdlib.h>

extern DeletionHelp *releasePool;

void insertNewNode(AST *newNode) {
    DeletionHelp delHelp = {.nodeRef = newNode, .next = releasePool};

    DeletionHelp *delHelpPointer = malloc(sizeof(DeletionHelp));
    *delHelpPointer = delHelp;
    releasePool = delHelpPointer;
}

void freeReleasePool() {
  
  while (releasePool != NULL) {
    DeletionHelp *temp = releasePool->next;
    freeLexicalValue(releasePool->nodeRef->value);
    free(releasePool->nodeRef);
    free(releasePool);
    releasePool = temp;
  }

}