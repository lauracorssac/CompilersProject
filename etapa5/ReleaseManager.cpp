/*

	LAURA BRAGANTE CORSSAC - 00274694

*/

#include "ReleaseManager.hpp"
#include <stdlib.h>
#include <list>

using namespace std;

ReleaseManager::ReleaseManager() {
  
}

void ReleaseManager::insertNewNode(AST *newNode) {
   this->releasePool.push_back(newNode);
}

void ReleaseManager::freeReleasePool() {
  
  list<AST *>::iterator it;
  for(it = this->releasePool.begin(); it != this->releasePool.end(); ++it) {
    delete *it;
  }

}