/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "ReleaseManager.hpp"
#include <stdlib.h>

ReleaseManager::ReleaseManager() {
  
}

void ReleaseManager::insertNewNode(AST *newNode) {
    DeletionHelp delHelp = {.nodeRef = newNode, .next = releasePool};

    DeletionHelp *delHelpPointer = (DeletionHelp *) malloc(sizeof(DeletionHelp));
    *delHelpPointer = delHelp;
    releasePool = delHelpPointer;
}

void ReleaseManager::freeReleasePool() {
  
  while (releasePool != NULL) {
    DeletionHelp *temp = releasePool->next;
    freeLexicalValue(releasePool->nodeRef->value);
    free(releasePool->nodeRef);
    free(releasePool);
    releasePool = temp;
  }

}