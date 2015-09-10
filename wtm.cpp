#include <iostream>
#include <vector>

#include "kmp.h"
#include "defs.h"

using namespace std;

unsigned int WTM ( unsigned char * x, unsigned int m, double ** y, unsigned int n, double z, unsigned char * alphabet )
{
	unsigned int sigma = strlen ( ( char * ) alphabet );
	unsigned int num_Occ = 0;

	/* Colouring y */
	unsigned char colour[n];
	unsigned char stry[n];
	unsigned int letter[n];
	vector < unsigned int > BP;

	for ( unsigned int i = 0; i < n; i++ )
	{
		double max_prob = 0;
		for ( unsigned int j = 0; j < sigma; j++ )
		{
			if ( max_prob < y[i][j] )
			{
				max_prob = y[i][j];
				letter[i] = j;
			}
		}
		if ( max_prob == 1 )
		{
			colour[i] = 'w';
			stry[i] = alphabet[ letter[i] ];
		}
		else if ( max_prob > 1/z )
		{
			colour[i] = 'g';
			stry[i] = alphabet[ letter[i] ];
		}
		else
		{
			colour[i] = 'b';
			stry[i] = '$';
			BP.push_back[i];
		}
	}

	unsigned int num_bp = BP.size();

	unsigned int s[n - m + 1];
	s[0] = 0;
	for ( unsigned int i = 0; i < m; i++ )
	{
		if ( colour[i] == 'b' )
			s[0] ++;
	}
	unsigned int max_s = s[0];
	for ( unsigned int i = 1; i < n - m + 1; i++ )
	{
		if ( colour[i - 1] == 'b' )
			s[i] = s[i - 1] - 1;
		if ( colour[i + m - 1] == 'b' )
			s[i] = s[i] + 1;
		if ( s[i] > max_s )
			max_s = s[i];
	}

	if ( max_s >=m )
	{
		cout << "Error: too many black positions in string y!" << endl;
		return 0;
	}

	unsigned int f = max_s + 1;				//the number of fragments

	int * ind = new int [f];				//the starting position of eacn fragments
	int * mf = new int [f];					//the length of each fragment

	for ( int j = 0; j < f; j++ )
		fragments ( 0, j, f, m, mf, ind );

	/* Check whether there exists duplicated fragments */
	char ** seqs;
	int	* dups = new int [f];

	unsigned int uniq;
	uniq = extract_dups_single_str ( x, m, f, mf, ind, dups );

	int * d_occ = new int [f];
	int * l_occ = new int [f];

	for ( unsigned int j = 0; j < f; j++ )
	{
		d_occ[j] = -1;
		l_occ[j] = -1;
	}

	/* In case there exist duplicated fragments */
	if ( uniq < f )
	{
		seqs = new char * [f];
		for ( unsigned int j = 0; j < f; j++ )
		{
			unsigned int f_id = j;

			/* Add the fragment once */
			if ( dups[f_id] < 0 )
			{
				seqs[f_id] = new char [ mf[f_id] + 1 ];
				memcpy( seqs[f_id], x + ind[f_id], mf[f_id] );
				seqs[f_id][ mf[f_id] ] = '\0';
			}
			else
			{
				seqs[f_id] = new char [1];
				seqs[f_id][0] = '\0';

				if ( l_occ[ dups[f_id] ] == -1 )	//if it is the first duplicated fragment
					d_occ[ dups[f_id] ] = f_id;
				else
					d_occ[ l_occ[ dups[f_id] ] ] = f_id;
				l_occ[ dups[f_id] ] = f_id;
			}
		}
	}
	else
	{
		seqs = new char * [f];
		for ( unsigned int j = 0; j < f; j++ )
		{
			unsigned int f_id = j;
			seqs[f_id] = new char [ mf[f_id] + 1 ];
			memcpy( seqs[f_id], x + ind[f_id], mf[f_id] );
			seqs[f_id][ mf[f_id] ] = '\0';
		}
	}

	int * F = new int [ALLOC_SIZE];
	int * P = new int [ALLOC_SIZE];

	int matches;

	gF = F;
	gP = P;

	filtering ( ( char * ) y, n, ( char ** ) seqs, f );

	F = gF;
	P = gP;
	matches = gMatches;

	for ( int i = 0; i < matches; i++ )
	{
		int jj = F[i];				//the ID of fragment
		do
		{
			if ( ( ind[jj] + mf[jj] >= P[jj] && ( n - P[i] >= m - mf[ii] - ind[ii];
			unsigned int ystart = P[i] - mf[jj];



















