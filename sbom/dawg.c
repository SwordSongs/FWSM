/* dawg.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listOfIntegers.h"
#include "automaton.h"
#include "listOfNumbers.h"

#define Primary   1
#define Secondary 0

Node dawgSplit(Node parentnode, Node childnode, unsigned char a,
               Automaton automaton) {
 Node root, newchildnode, currentnode;
 int b, ind;

 root = automaton->root;
 newchildnode = automaton->nodeCounter++;
 terminal(newchildnode) = terminal(childnode);
 delta(parentnode, a) = newchildnode;
 primary(parentnode, a) = Primary;
 for (b = 0; b < ASIZE; ++b)
    if (delta(childnode, b) != UNDEFINED) {
       delta(newchildnode, b) = delta(childnode, b);
       primary(newchildnode, b) = Secondary;
    }
 failure(newchildnode) = failure(childnode);
 failure(childnode) = newchildnode;
 currentnode = parentnode;
 while (currentnode != root) {
    currentnode = failure(currentnode);
    ind = 0;
    for (b = 0; b < ASIZE; ++b)
       if (delta(currentnode, b) == childnode)
          if (primary(currentnode, b) == Secondary) {
             delta(currentnode, b) = newchildnode;
             primary(currentnode, b) = Secondary;
             ind = 1;
          }
          else break;
    if (!ind) break;
 }
 return newchildnode;
}



Node dawgUpdate(Node activenode, unsigned char a, Automaton automaton) {
   Node root, newactivenode, currentnode, suffixnode;

   newactivenode = delta(activenode, a);
   if (newactivenode != UNDEFINED) {
      if (primary(activenode, a)) return newactivenode;
      else return dawgSplit(activenode, newactivenode, a, automaton);
   }
   else {
     root = automaton->root;
     newactivenode = automaton->nodeCounter++;
     delta(activenode, a) = newactivenode;
     primary(activenode, a) = Primary;
     currentnode = activenode;
     suffixnode = UNDEFINED;
     while (currentnode != root && suffixnode == UNDEFINED) {
        currentnode = failure(currentnode);
        if (delta(currentnode, a) != UNDEFINED)
           if (primary(currentnode, a))
              suffixnode = delta(currentnode, a);
           else
              suffixnode = dawgSplit(currentnode, delta(currentnode, a), a, automaton);
        else {
           delta(currentnode, a) = newactivenode;
           primary(currentnode, a) = Secondary;
        }
     }
     failure(newactivenode) = (suffixnode != UNDEFINED ? suffixnode : root);
     return newactivenode;
   }
}



Automaton buildDawg(unsigned char **tableOfPatterns, int k) {
   Automaton automaton;
   Node root, activenode;
   int i, j, ell, M, m;

   automaton=(Automaton)malloc(sizeof(struct _automaton));
   for (i=M=0; i < k; ++i) {
      M+=strlen((char*)tableOfPatterns[i]);
   }
   automaton->trans=(int *)calloc(2*M*ASIZE, sizeof(int));
   automaton->prim=(char *)calloc(2*M*ASIZE, sizeof(int));
   automaton->term=(char *)calloc(2*M, sizeof(int));
   automaton->fail=(int *)calloc(2*M, sizeof(int));
   automaton->list=(ListOfIntegers *)calloc(2*M, sizeof(struct _listOfIntegers));
   
   automaton->nodeCounter = 1;
   automaton->root = automaton->nodeCounter++;
   root = automaton->root;
   failure(root) = root;
   for (j = 0; j < k; ++j) {
      activenode = root;
      m = strlen((char*)tableOfPatterns[j]);
      for (ell = m-1; ell >= 0; --ell) {
         activenode = dawgUpdate(activenode, tableOfPatterns[j][ell], automaton);
      }
      addNodePatternNumber(activenode, j, automaton);
      do {
         terminal(activenode) = 1;
         activenode = failure(activenode);
      }
      while (activenode != root);
 }
 return automaton;
}
