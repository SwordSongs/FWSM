/* dawg.h */

Node dawgSplit(Node parentnode, Node childnode, unsigned char a,
               Automaton automaton);
Node dawgUpdate(Node activenode, unsigned char a, Automaton automaton);
Automaton buildDawg(unsigned char **tableOfPatterns, int k);
