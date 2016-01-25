#include <iostream>
#include <vector>
#include <string>

#include "defs.h"

using namespace std;

STRINGS xy;

void preparation ( string x, double ** y, unsigned int n, double z, string alphabet, int mod )
{
	unsigned int sigma = alphabet.size();
	unsigned int bpl = sigma ;
	unsigned int m = x.size();

	vector < unsigned int > xstr;
	vector < unsigned int > ystr;
	vector < unsigned int > yBP;
	vector < double > yprob;
	vector < vector < double > > ybptable;

	xstr.reserve ( m );

	for ( unsigned int i = 0; i < m; i++ )
	{
		xstr.push_back ( alphabet.find ( x[i] ) );
	}

	ystr.reserve ( n );
	yprob.reserve ( n );

	for ( unsigned int i = 0; i < n; i++ )
	{
		double max = 0;
		unsigned int letter = 0;
		for ( unsigned int j = 0; j < sigma; j++ )
		{
			if ( max < y[i][j] )
			{
				max = y[i][j];
				letter = j;
			}
		}
		if ( max >= 1 - 1/z )
		{
			ystr.push_back ( letter );
			yprob.push_back ( max );
		}
		else
		{
			vector < double > yi;
			yi.assign ( y[i], y[i] + sigma );
			ystr.push_back ( bpl );
			yprob.push_back ( 0 );
			ybptable.push_back ( yi );
			yBP.push_back ( i );
			bpl ++;
		}
	}

	if ( mod == 1 )
	{
		/* WPM case */
		xy.pattern = ystr;
		xy.text = xstr;
		xy.BP = yBP;
		xy.prob = yprob;
		xy.bptable = ybptable;
	}
	else if ( mod == 2 )
	{
		/* WTM case */
		xy.pattern = xstr;
		xy.text = ystr;
		xy.BP = yBP;
		xy.prob = yprob;
		xy.bptable = ybptable;
	}
	xstr.clear();
	ystr.clear();
	yprob.clear();

	vector < unsigned int > ().swap ( xstr );
	vector < unsigned int > ().swap ( ystr );
	vector < double > ().swap ( yprob );
}

