// oracle.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listOfIntegers.h"
#include "automaton.h"
#include "oracle.h"
#include "listOfNumbers.h"
#include "triple.h"
#include "fifo.h"


///////////////////////////////////////////////////////////////////////////////
// Enter a pattern in the trie (rooted at root)
//
void enterOracle(unsigned char *pattern, int j, int lmin, Automaton automaton) {
   Node node, nodeTmp, nodeNew;
   int i;

   node = automaton->root;
   i = lmin-1;
   while (i >= 0 && (nodeTmp = delta(node, pattern[i])) != 0) {
     node = nodeTmp;
     --i;
   }
   while (i >= 0) {
      nodeNew = automaton->nodeCounter++;
      delta(node, pattern[i]) = nodeNew;
      node = nodeNew;
      --i;
   }
   terminal(node) = 1;
   addNodePatternNumber(node, j, automaton);
}

///////////////////////////////////////////////////////////////////////////////
// Build a trie with the list of patterns
//
void buildTrieOracle(unsigned char **X, int k, int lmin, Automaton automaton) {
   Node root;
   int i;

   automaton->root = automaton->nodeCounter++;
   for (i=0; i < k; ++i) {
      enterOracle(X[i], i, lmin, automaton);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Build the oracle with the list of patterns
//
Automaton buildOracle(unsigned char **X, int k, int  lmin) {
   Automaton automaton;
   Node parent, current, down, nodeTmp;
   unsigned char sigma;
   Fifo fifo;
   Triple triple;
   int i, M;

   automaton=(Automaton)malloc(sizeof(struct _automaton));
   for (i=M=0; i < k; ++i) M+=strlen((char*)X[i]);
   automaton->trans=(int *)calloc((M+2)*ASIZE, sizeof(int));
   automaton->term=(char *)calloc((M+2), sizeof(int));
   automaton->fail=(int *)calloc((M+2), sizeof(int));
   automaton->list=(ListOfIntegers *)calloc((M+2), sizeof(struct _listOfIntegers));
   
   automaton->nodeCounter = 1;
   buildTrieOracle(X, k, lmin, automaton);
   fifo = newFifo(automaton);
   failure(automaton->root) = 0;
   while (!isFifoEmpty(fifo)) {
      triple = getFifoFirst(fifo);
      parent = getTripleSource(triple);
      sigma = getTripleLetter(triple);
      current = getTripleTarget(triple);
      free(triple);
      addFifoTransitions(fifo, current, automaton);
      down = failure(parent);
      while (down != 0 && (nodeTmp = delta(down, sigma)) == 0) {
         delta(down, sigma) = current;
	 down = failure(down);
      }
      if (down != 0) failure(current) = nodeTmp;
      else failure(current) = automaton->root;
   }
   return automaton;
}


///////////////////////////////////////////////////////////////////////////////
// Build a trie with the list of patterns
//
void buildTrieMyOracle(unsigned char **X, int k, int lmin, Automaton automaton) {
   Node root;
   int i;

   automaton->root = automaton->nodeCounter++;
   for (i=0; i < k; ++i) {
      enterOracle(X[i], i, strlen((char*)X[i]), automaton);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Build the oracle with the list of patterns
//
Automaton buildMyOracle(unsigned char **X, int k, int  lmin) {
   Automaton automaton;
   Node parent, current, down, nodeTmp;
   unsigned char sigma;
   Fifo fifo;
   Triple triple;
   int i, M;

   automaton=(Automaton)malloc(sizeof(struct _automaton));
   for (i=M=0; i < k; ++i) M+=strlen((char*)X[i]);
   automaton->trans=(int *)calloc((M+2)*ASIZE, sizeof(int));
   automaton->term=(char *)calloc((M+2), sizeof(int));
   automaton->fail=(int *)calloc((M+2), sizeof(int));
   automaton->list=(ListOfIntegers *)calloc((M+2), sizeof(struct _listOfIntegers));
   
   automaton->nodeCounter = 1;
   buildTrieMyOracle(X, k, lmin, automaton);
   fifo = newFifo(automaton);
   failure(automaton->root) = 0;
   while (!isFifoEmpty(fifo)) {
      triple = getFifoFirst(fifo);
      parent = getTripleSource(triple);
      sigma = getTripleLetter(triple);
      current = getTripleTarget(triple);
      free(triple);
      addFifoTransitions(fifo, current, automaton);
      down = failure(parent);
      while (down != 0 && (nodeTmp = delta(down, sigma)) == 0) {
         delta(down, sigma) = current;
	 down = failure(down);
      }
      if (down != 0) failure(current) = nodeTmp;
      else failure(current) = automaton->root;
   }
   return automaton;
}
