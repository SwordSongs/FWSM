#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>

#include "defs.h"
#include "global.h"
#include "aca.h"

using namespace std;

int * gF = NULL;
int * gP = NULL;
int gMatches = 0;

unsigned int WTM ( double z, string alphabet, vector < unsigned int > * Occ )
{
	cout << "123" << endl;
	unsigned int sigma		= alphabet.size();
	unsigned int m			= xy.pattern.size();
	unsigned int n			= xy.text.size();
	unsigned char * x		= new unsigned char [m];
	unsigned char * y		= new unsigned char [n];
	unsigned int l			= ceil ( log ( z ) / log ( z / ( z - 1 ) ) );
	unsigned int num_frag	= l + 1;
	unsigned int num_Occ	= 0;

	if ( num_frag > m )
	{
		num_frag = m;
	}

	for ( unsigned int i = 0; i < m; i++ )
	{
		x[i] = alphabet[ xy.pattern[i] ];
	}

	for ( unsigned int i = 0; i < m; i++ )
	{
		cout << x[i];
	}
	cout << endl;

	for ( unsigned int i = 0; i < n; i++ )
	{
		unsigned int ch = xy.text[i];
		if ( ch < sigma )
		{
			y[i] = alphabet[ch];
		}
		else
		{
			y[i] = '$';
		}
	}

	for ( unsigned int i = 0; i < n; i++ )
	{
		cout << y[i];
	}
	cout << endl;

	Factor * F	= new Factor [num_frag];
	int	*	ind	= new int [num_frag];		//the starting position of fragments
	int	*	mf	= new int [num_frag];		//the length of fragments

	for ( unsigned int i = 0; i < num_frag; i++ )
	{
		fragments ( 0, i, num_frag, m, mf, ind );
		F[i].length	= mf[i];
		F[i].start	= ind[i];
		F[i].end	= ind[i] + mf[i] - 1;
		F[i].prob	= 1;
	}

	/* Check whether there exist duplicated fragments */
	unsigned char ** seqs;
	seqs = new unsigned char * [num_frag];
	for ( unsigned int i = 0; i < num_frag; i++ )
	{
		seqs[i] = new unsigned char [ mf[i] + 1 ];
		memmove ( seqs[i], x + ind[i], mf[i] );
		seqs[i][ mf[i] ] = '\0';
		for ( unsigned int j = 0; j < mf[i]; j++ )
			cout << seqs[i][j] << ' ';
		cout << endl;
	}
#if 0
	int	 *	dups;

	dups = new int [num_frag];
	unsigned int uniq;
	uniq = extract_dups_single_str ( x, m, num_frag, mf, ind, dups );

	int * d_occ = new int [num_frag];
	int * l_occ = new int [num_frag];

	for ( unsigned int i = 0; i < num_frag; i++ )
	{
		d_occ[i] = -1;
		l_occ[i] = -1;
	}

	/* In case there exist duplicated fragments */
	if ( uniq < num_frag ) 
	{
		seqs = new unsigned char * [num_frag];
		for ( unsigned int i = 0; i < num_frag; i++ )
		{
			/* Add the fragment once */
			if ( dups[i] < 0 )
			{
				seqs[i] = new unsigned char [ mf[i] + 1 ];
				memmove ( seqs, x + ind[i], mf[i] );
				seqs[i][i] = '\0';
			}
			else
			{
				/* add nothing since it is already added */
				seqs[i] = new unsigned char [1];
				seqs[i][0] = '\0';

				if ( l_occ[dups[i]] == -1 )
					d_occ[dups[i]] = i;
				else
					d_occ[ l_occ[ dups[i] ] ] = i;
				l_occ[dups[i]] = i;
			}
		}
	}
	else
	{
		/* all all the fragments since there exist no duplicated fragments */
		seqs = new unsigned char * [num_frag];
		for ( unsigned int i = 0; i < num_frag; i++ )
		{
			seqs[i] = new unsigned char [ mf[i] + 1 ];
			memmove ( seqs[i], x + ind[i], mf[i] );
			seqs[i][mf[i]] = '\0';
		}
	}
#endif
	int * frag_id	= new int [10000];
	int * frag_occ	= new int [10000];
	unsigned int matches;
	
	gF = frag_id;
	gP = frag_occ;
	matches = gMatches;

	filtering ( ( char * ) y, n, ( char ** ) seqs, num_frag );

	frag_id	 = gF;
	frag_occ = gP;
	matches = gMatches;

	cout << "matches=" << matches << endl;

	for ( unsigned int i = 0; i < matches; i++ )
	{
		int id = frag_id[i];
		cout << "id=" << frag_id[i] << "\tocc=" << frag_occ[i] << endl;
//		do 
//		{
			if ( ( frag_occ[i] >= F[id].start ) && ( n - frag_occ[i] >= m - F[id].start ) )
			{
				unsigned int ystart = frag_occ[i] - F[id].start;
				unsigned int flag = 1;
				double prob_Occ = F[id].prob;

				unsigned int j = 0;
				while ( j < m )
				{
					if ( xy.text[ystart + j] < sigma )
					{
						if ( xy.text[ystart + j] != xy.pattern[j] )
						{
							flag = 0;
							break;
						}
						else
						{
							prob_Occ *= xy.prob[j];
							if ( prob_Occ < 1/z )
							{
								flag = 0;
								break;
							}
							else
							{
								j++;
							}
						}
					}
					else
					{
						unsigned int row = xy.text[ystart + j] - sigma;
						unsigned int col = xy.pattern[j];
						prob_Occ *= xy.bptable[row][col];
						if ( prob_Occ < 1/z )
						{
							flag = 0;
							break;
						}
						else
						{
							j++;
						}
					}
					if ( j == F[id].start )
					{
						j = F[id].end + 1;
					}
				}
				if ( flag )
				{
					Occ->push_back( ystart );
					num_Occ ++;
				}
			}
//		} while ( id != -1 );
	}

	delete[] F;
	delete[] ind;
	delete[] mf;
	delete[] frag_id;
	delete[] frag_occ;
	for ( unsigned int i = 0; i < num_frag; i++ )
		delete[] seqs[i];
	delete[] seqs;

	cout << "num_Occ=" << num_Occ << endl;
	return num_Occ;
}


				




