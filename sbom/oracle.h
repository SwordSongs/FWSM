// oracle.h

void enterOracle(unsigned char *pattern, int j, int lmin, Automaton automaton);
void buildTrieOracle(unsigned char **tableOfPatterns, int k, int lmin, Automaton automaton);
Automaton buildOracle(unsigned char **tableOfPatterns, int k, int  lmin);
