// automaton.h

struct _automaton {
   int *trans,
       *fail,
       *sh,
       root,
       currentState,
       nodeCounter;
   char *term,
        *prim;
   ListOfIntegers *list;
   int *_depth;
};

typedef struct _automaton *Automaton;
typedef int Node;

#define ASIZE 256
#define UNDEFINED 0
#define delta(q,a) automaton->trans[(q)*ASIZE+(a)]
#define primary(q,a) automaton->prim[(q)*ASIZE+(a)]
#define failure(q) automaton->fail[(q)]
#define terminal(q) automaton->term[(q)]
#define shift(q) automaton->sh[(q)]
#define depth(q) automaton->_depth[(q)]

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
