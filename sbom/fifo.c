// fifo.c

#include <stdio.h>
#include <stdlib.h>
#include "listOfIntegers.h"
#include "automaton.h"
#include "triple.h"
#include "fifo.h"


// Methods of Fifo

///////////////////////////////////////////////////////////////////////////////
// Create a new queue with the transitions of node
//
Fifo newFifo(Automaton automaton) {
   Fifo newF;
   int i;

   newF = (Fifo)malloc(sizeof(struct _fifo));
   setFifoHead(newF, NULL);
   setFifoTail(newF, NULL);
   for (i=0; i < ASIZE; ++i)
      if (delta(automaton->root, i) != 0)
         addFifo(newF, newTriple(automaton->root, i, delta(automaton->root, i)));
   return newF;
}

///////////////////////////////////////////////////////////////////////////////
// Push in the queue the transitions of node
//
void addFifoTransitions(Fifo fifo, Node node, Automaton automaton) {
   int i;

   for (i=0; i < ASIZE; ++i) {
      if (delta(node, i) != UNDEFINED) {
         addFifo(fifo, newTriple(node, i, delta(node, i)));
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Set the head
//
void setFifoHead(Fifo fifo, Triple head) {
   fifo->head = head;
}

///////////////////////////////////////////////////////////////////////////////
// Get the head
//
Triple getFifoHead(Fifo fifo) {
   return fifo->head;
}

///////////////////////////////////////////////////////////////////////////////
// Set the tail
//
void setFifoTail(Fifo fifo, Triple tail) {
   fifo->tail = tail;
}

///////////////////////////////////////////////////////////////////////////////
// Get the tail
Triple getFifoTail(Fifo fifo) {
   return fifo->tail;
}

///////////////////////////////////////////////////////////////////////////////
// Push a triple at the tail of the queue
//
void addFifo(Fifo fifo, Triple triple) {
   if (getFifoHead(fifo) == NULL) {
      setFifoHead(fifo, triple);
      setFifoTail(fifo, triple);
   }
   else {
      setTripleNext(getFifoTail(fifo), triple);
      setFifoTail(fifo, triple);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Test in the queue is empty
//
int isFifoEmpty(Fifo fifo) {
   return getFifoHead(fifo) == NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Pop the element at the head of the queue
//
Triple getFifoFirst(Fifo fifo) {
   Triple triple;

   triple = getFifoHead(fifo);
   setFifoHead(fifo, getTripleNext(triple));
   if (getFifoHead(fifo) == NULL)
      setFifoTail(fifo, NULL);
   return triple;
}
