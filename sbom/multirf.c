// multirf.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listOfIntegers.h"
#include "automaton.h"
#include "dawg.h"
#include "sm.h"


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Multi Reverse Factor
void MultiRF(unsigned char **X, int k, unsigned char *y, int n) {
   Automaton automaton;
   Node root, state;
   int i, j, lmin, lmax, p;
   ListOfIntegers cell;

   automaton = buildDawg(X, k);
   root = automaton->root;
   lmin = lmax = strlen((char*)X[0]);
   for (i=1; i < k; ++i) {
      if (strlen((char*)X[i]) < lmin) {
         lmin = strlen((char*)X[i]);
      }
      else if (strlen((char*)X[i]) > lmax) {
         lmax = strlen((char*)X[i]);
      }
   }
   --lmax;
   memcpy(y+n, X[0], strlen((char*)X[0]));
   j = lmin-1;
   while (1) {
      while (delta(root, y[j]) == UNDEFINED) {
         j += lmin;
      }
      state = delta(root, y[j]);
      i=j-1;
      if (terminal(state)) p=j;
      else p=j+1;
      while (delta(state, y[i]) != UNDEFINED) {
         state = delta(state, y[i]);
         for (cell = automaton->list[state]; cell != NULL; cell = cell->next) {
            if (strlen((char*)X[cell->element]) == j-i+1)
               if (j < n) OUTPUT(j-strlen((char*)X[cell->element])+1, cell->element);
               else {
                  free(automaton->trans);
                  free(automaton->term);
                  free(automaton->fail);
                  for (i = automaton->root; i < automaton->nodeCounter; ++i)
                     freeListOfIntegers(automaton->list[i]);
                  free(automaton->list);
                  free(automaton);
                  return;
               }
         }
         if (terminal(state))
            p=i;
         --i;
      }
      j=MAX(p+lmin-1, j+1);
   }
}
