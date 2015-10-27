// fifo.h

struct _fifo {               // A queue with
   Triple head, tail;        //  a head and a tail
};

typedef struct _fifo *Fifo;


// Méthodes de Fifo

Fifo newFifo(Automaton automaton);
void addFifoTransitions(Fifo fifo, Node node, Automaton automaton);
void setFifoHead(Fifo fifo, Triple head);
Triple getFifoHead(Fifo fifo);
void setFifoTail(Fifo fifo, Triple tail);
Triple getFifoTail(Fifo fifo);
void addFifo(Fifo fifo, Triple triple);
int isFifoEmpty(Fifo fifo);
Triple getFifoFirst(Fifo fifo);
