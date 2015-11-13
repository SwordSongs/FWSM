// listOfNumbers.c

#include <stdio.h>
#include <stdlib.h>
#include "listOfIntegers.h"
#include "automaton.h"
#include "listOfNumbers.h"

///////////////////////////////////////////////////////////////////////////////
// The last cell of the list of numbers of p will point to the first cell of
//  the list of numbers of q
//
void includePatternNumbers(Node p, Node q, Automaton automaton) {
   ListOfIntegers cell;

   if (automaton->list[p] == NULL)
      automaton->list[p] = automaton->list[q];
   else if (automaton->list[p]->next == NULL)
      automaton->list[p]->next = automaton->list[q];
   else {
      for (cell=automaton->list[p]; cell->next != NULL; cell = cell->next);
      cell->next = automaton->list[q];
   }
}

///////////////////////////////////////////////////////////////////////////////
// Add j in the list of pattern numbers of node
//
void addNodePatternNumber(Node node, int j, Automaton automaton) {
   ListOfIntegers newL;

   newL = newListOfIntegers(j);
   setListOfIntegersNext(newL, automaton->list[node]);
   automaton->list[node]=newL;
}
