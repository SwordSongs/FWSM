#include <iostream>
#include <vector>
#include <map>
#include <cstring>

#include "kmp.h"
#include "defs.h"

using namespace std;

unsigned int WMP ( double ** x, unsigned int m, unsigned char * y, unsigned int n, double z, unsigned char * alphabet, unsigned int * Occ )
{
	unsigned int sigma = strlen ( ( char * )alphabet );		//size of alphabet
	unsigned int num_Occ = 0;						//the number of occurrence of x in y
	/* Colouring */
	unsigned char colour[m];						//colour of string
	unsigned char strx[m];							//make a string of x, using $ at black position
	unsigned int letter[m];
	vector < unsigned int > BP;						//saving the position of each black
	for ( unsigned int i = 0; i < m; i++ )
	{
		double max_prob = 0;
		for ( unsigned int j = 0; j < sigma; j++ )
		{
			if ( max_prob < x[i][j] )
			{
				max_prob = x[i][j];
				letter[i] = j;
			}
		}
		if ( max_prob == 1 )
		{
			colour[i] = 'w';
			strx[i] = alphabet[ letter[i] ];
		}
		else if ( max_prob > 1 - 1/z )
		{
			colour[i] = 'g';
			strx[i] = alphabet[ letter[i] ];
		}
		else
		{
			colour[i] = 'b';
			strx[i] = '$';
			BP.push_back ( i );
		}
	}

	unsigned int num_bp = BP.size();
	
	if ( num_bp >= m )								//the number of black position must be smaller than the length of x
	{
		cout << "Error: too many black position in weighted string x!" << endl;
		return 0;
	}
	
	/* Find the longest factor f in x with no black position */
	Factor f;
	f.length = 0;
	f.prob = 1;

	for ( unsigned int i = 1; i < num_bp; i++ )
	{
		if ( f.length < BP[i] - BP[i-1] - 1 )
		{
			f.length = BP[i] - BP[i-1] - 1;
			f.start = BP[i-1] + 1;
			f.end = BP[i] - 1;
		}
	}

	f.str = new unsigned char [f.length + 1];
	memcpy ( f.str, strx + f.start, f.length );
	f.str[f.length] = '\0';

	for ( unsigned int i = f.start; i < f.end + 1; i++ )
	{
		f.prob *= x[i][ letter[i] ];
	}

	/* Search for f in y using algorithm KMP */
	vector < unsigned int > fOcc;
	KMP ( f.str, f.length, y, n, &fOcc );
	unsigned int num_fOcc = fOcc.size();

	unsigned int y_int[n];
	for ( unsigned int i = 0; i < n; i++ )
	{
		for ( unsigned int j = 0; j < sigma; j++ )
		{
			if ( y[i] == alphabet[j] )
				y_int[i] = j;
		}
	}

	/* For each occurrence of f in y, try to extense */
	for ( unsigned int i = 0; i < num_fOcc; i++ )
	{
		if ( ( fOcc[i] >= f.start ) && ( n - fOcc[i] >= m - f.start ) )
		{
			unsigned int ystart = fOcc[i] - f.start;
			unsigned int flag = 1;										//Check if f is extendible, 1 for extendible
			double prob_Occ = f.prob;									//the probability of occurrence
			if ( prob_Occ >= 1/z )
			{
				for ( unsigned int j = 0; j < f.start; j++ )				//extense to the left
				{
					prob_Occ *= x[j][ y_int[ystart + j] ];
					if ( prob_Occ < 1/z )
					{
						flag = 0;
						break;
					}
				}
			}
			if ( prob_Occ >= 1/z )
			{
				for ( unsigned int j = f.end + 1; j < m; j++ )
				{
					prob_Occ *= x[j][ y_int[ystart + j] ];
					if ( prob_Occ < 1/z )
					{
						flag = 0;
						break;
					}
				}
			}
			if ( flag )
			{
				Occ[num_Occ] = ystart;
				num_Occ ++;
			}
		}
	}

	delete [] f.str;

	return num_Occ;
}


