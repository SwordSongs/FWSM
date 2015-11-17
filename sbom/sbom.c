// sbom.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listOfIntegers.h"
#include "automaton.h"
#include "oracle.h"
#include "sm.h"
#include "sbom.h"


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Set Backward Oracle Matching
int SBOM(unsigned char **x, int k, int uniq, unsigned char *y, int n, int * F, int * P) {
   int i, j, lmin, p;
   Automaton automaton;
   Node current, root;
   ListOfIntegers cell;
   int num_occ = 0;
   unsigned char ** X;
   X = ( unsigned char ** ) malloc ( uniq * sizeof ( unsigned char * ) );
	
   int qq = 0;
   for ( int q = 0; q < k; q++ )
   {
	   if ( sizeof ( ( char * ) x[q] ) > 1 )
	   {
		   X[qq] = x[q];
		   ++ qq;
	   }
   }

   k = uniq;

   lmin = strlen((char*)X[0]);
   for (i=1; i < k; ++i) {
      if (strlen((char*)X[i]) < lmin) lmin = strlen((char*)X[i]);
   }
   automaton = buildOracle(X, k, lmin);
   root = automaton->root;
   j = lmin-1;
   memcpy(y+n, X[0], strlen((char*)X[0]));
   while (1) {
      while (delta(root, y[j]) == UNDEFINED)
         j += lmin;
      current = delta(root, y[j]);
      i = 1;
      do {
         current = delta(current, y[j-i]);
         ++i;
      } while (i < lmin && current != UNDEFINED);
      if (current != UNDEFINED && i >= lmin) {
         if (automaton->list[current] != NULL) {
            p = (automaton->list[current])->element;
            if (memcmp(y+j-i+1, X[p], lmin) == 0) {
               for (cell = automaton->list[current]; cell != NULL; cell = cell->next) {
                  if (memcmp(y+j+1, X[cell->element]+lmin, strlen((char*)X[cell->element])-lmin) == 0) {
                     if (j < n)
					 {
						 P[num_occ] = j - i + 1;
						 F[num_occ]  = cell->element;
						 num_occ++;
					 }
                     else {
                        free(automaton->trans);
                        free(automaton->term);
                        free(automaton->fail);
                        for (i = automaton->root; i < automaton->nodeCounter; ++i)
                           freeListOfIntegers(automaton->list[i]);
                        free(automaton->list);
                        free(automaton);
                        return num_occ;
                     }
                  }
               }
            }
         }
         ++j;
      }
      else {
         j += (lmin-i)+1;
      }
   }

   free ( X );

   return num_occ;
}
