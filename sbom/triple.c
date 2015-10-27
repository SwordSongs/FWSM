// triple.c

#include <stdio.h>
#include <stdlib.h>
#include "listOfIntegers.h"
#include "automaton.h"
#include "triple.h"

// Methodes of Triple

///////////////////////////////////////////////////////////////////////////////
// Create a new triple
//
Triple newTriple(Node source, unsigned char letter, Node target) {
   Triple newT;

//printf("newTriple source = %d, letter = %c target = %d\n", source, letter, target);
   newT = (Triple)malloc(sizeof(struct _triple));
   newT->source = source;
   newT->letter = letter;
   newT->target = target;
   newT->next = NULL;
   return newT;
}

///////////////////////////////////////////////////////////////////////////////
// Set the source
//
void setTripleSource(Triple triple, Node source) {
   triple->source = source;
}

///////////////////////////////////////////////////////////////////////////////
// Get the source
//
Node getTripleSource(Triple triple) {
   return triple->source;
}

///////////////////////////////////////////////////////////////////////////////
// Set the letter
//
void setTripleLetter(Triple triple, unsigned char letter) {
   triple->letter = letter;
}

///////////////////////////////////////////////////////////////////////////////
// Get the letter
//
unsigned char getTripleLetter(Triple triple) {
   return triple->letter;
}

///////////////////////////////////////////////////////////////////////////////
// Set the target
//
void setTripleTarget(Triple triple, Node target) {
   triple->target = target;
}

///////////////////////////////////////////////////////////////////////////////
// Get the target
//
Node getTripleTarget(Triple triple) {
   return triple->target;
}

///////////////////////////////////////////////////////////////////////////////
// Set the next
//
void setTripleNext(Triple triple, Triple next) {
   triple->next = next;
}

///////////////////////////////////////////////////////////////////////////////
// Get the next
//
Triple getTripleNext(Triple triple) {
   return triple->next;
}
