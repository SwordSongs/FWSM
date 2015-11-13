// triple.h

struct _triple {          // Triples are used for a breadth-first scan of the trie. They have:
   Node source, target;   //  - a source and a target node
   unsigned char letter;           //  - a label
   struct _triple *next;  // They point to the next triple
};

typedef struct _triple *Triple;

// Méthodes de Triple

Triple newTriple(Node source, unsigned char letter, Node target);
void setTripleSource(Triple triple, Node source);
Node getTripleSource(Triple triple);
void setTripleLetter(Triple triple, unsigned char letter);
unsigned char getTripleLetter(Triple triple);
void setTripleTarget(Triple triple, Node target);
Node getTripleTarget(Triple triple);
void setTripleNext(Triple triple, Triple next);
Triple getTripleNext(Triple triple);
