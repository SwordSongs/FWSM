#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "kmp.h"
#include "defs.h"
#include "global.h"

using namespace std;

unsigned int WPM ( double z, string alphabet, vector < unsigned int > * Occ )
{
	unsigned int sigma = alphabet.size();		//size of alphabet
	unsigned int num_Occ = 0;					//the number of occurrence of x in y
	unsigned int m = xy.pattern.size();			//length of pattern
	unsigned int n = xy.text.size();			//length of text

	unsigned int num_bp = xy.BP.size();
	
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
		if ( f.length < xy.BP[i] - xy.BP[i-1] - 1 )
		{
			f.length = xy.BP[i] - xy.BP[i-1] - 1;
			f.start = xy.BP[i-1] + 1;
			f.end = xy.BP[i] - 1;
		}
	}

	f.str = &xy.pattern[f.start];

	for ( unsigned int i = f.start; i < f.end + 1; i++ )
	{
		f.prob *= xy.prob[i];
	}

	/* Search for f in test using algorithm KMP */
	unsigned int * y = &xy.text[0];
	vector < unsigned int > fOcc;
	KMP ( f.str, f.length, y, n, &fOcc );
	unsigned int num_fOcc = fOcc.size();

	/* For each occurrence of f in y, try to extense */
	for ( unsigned int i = 0; i < num_fOcc; i++ )
	{
		if ( ( fOcc[i] >= f.start ) && ( n - fOcc[i] >= m - f.start ) )
		{
			unsigned int ystart = fOcc[i] - f.start;
			unsigned int flag = 1;										//Check if f is extendible, 1 for extendible
			double prob_Occ = f.prob;									//the probability of occurrence
			if ( prob_Occ < 1/z )										//if the pattern is not valid
			{
				flag = 0;
			}
			else
			{
				unsigned int j = 0;
				while ( j < m )
				{
					if ( xy.pattern[j] < sigma )						//if the letter in pattern is not black
					{
						if ( xy.text[ystart + j] != xy.pattern[j] )
						{
							flag = 0;
							break;
						}
						else
						{
							prob_Occ *= xy.prob[j];
							if ( prob_Occ < 1/z )						//if the probability is not valid
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
						unsigned int row = xy.pattern[j] - sigma;
						unsigned int col = xy.text[ystart + j];
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
					if ( j == f.start )
					{
						/* when left extension meets the factor, jump the factor */
						j = f.end + 1;
					}
				}
			}
			if ( flag )
			{
				Occ->push_back ( ystart );
				num_Occ ++;
			}
		}
	}

	return num_Occ;
}


