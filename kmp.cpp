#include <vector>

#include "kmp.h"

using namespace std;

void preKMP ( unsigned int * x, unsigned int m, int kmpNext[] )
{
	int i, j;

	i = 0;
	j = kmpNext[0] = -1;
	while ( i < m )
	{
		while ( j > -1 && x[i] != x[j] )
			j = kmpNext[j];
		i++;
		j++;
		if ( x[i] == x[j] )
			kmpNext[i] = kmpNext[j];
		else
			kmpNext[i] = j;
	}
}

void KMP ( unsigned int * x, unsigned int m, unsigned int * y, unsigned int n, vector < unsigned int > * Occ )
{
	int i, j;

	int kmpNext[m + 1];

	/* Preprocessing */
	preKMP ( x, m, kmpNext );

	/* Searching */
	i = j = 0;
	while ( j < n )
	{
		while ( i > -1 && x[i] != y[j] )
			i = kmpNext[i];
		i++;
		j++;
		if ( i >=m )
		{
			Occ->push_back ( j - i );
			i = kmpNext[i];
		}
	}
}

