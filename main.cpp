#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#include "defs.h"
#include "global.h"

using namespace std;

int main (int argc, char **argv)
{
	TSwitch sw;
	string alphabet;
	unsigned int sigma;
	int mod;
	string pattern_file;
	string text_file;
	string output;
	double z;
	string x;				//normal string
	unsigned int m;			//length of x
	double ** y;			//weighted string
	unsigned int n;			//length of y
	WStr xystr;

	clock_t start;
	clock_t finish;

	unsigned int k;

	/* Decodes the arguments */
	k = decode_switches ( argc, argv, &sw );

	/* Check the arguments */
	if ( k < 9 )
	{
		usage();
		return 1;
	}
	else
	{
		if ( sw.alphabet.compare ( "DNA" ) == 0 )
		{
			alphabet = DNA;
			sigma = alphabet.size();
		}
		else if ( sw.alphabet.compare ( "dna" ) == 0 )
		{
			alphabet = dna;
			sigma = alphabet.size();
		}
		else
		{
			cout << "Error: Only support DNA alphabet up to now!" << endl;
			return 0;
		}

		mod = sw.mod;
		if ( sw.mod > 2 )
		{	
			cout << "Error: Mode (-m) not correct!" << endl;
			return 0;
		}
		else
		{
			mod = sw.mod;
		}

		if ( sw.pattern_file_name.size() == 0 )
		{
			cout << "Error: No Pattern input!" << endl;
			return 0;
		}
		else
		{
			pattern_file = sw.pattern_file_name;
		}

		if ( sw.text_file_name.size() == 0 )
		{
			cout << "Error: No Text input!" << endl;
			return 0;
		}
		else
		{
			text_file = sw.text_file_name;
		}

		if ( sw.output_filename.size() == 0 )
		{
			output = "MatchingReport";		
		}
		else
		{
			output = sw.output_filename;
		}

		if ( z > 0 )
		{
			z = sw.z;
		}
		else 
		{
			cout << "Error: z must be a position integer!" << endl;
		}
	}

	/* read input Weighted String */
	ifstream fpattern ( pattern_name );
	ifstream ftext ( text_name );
	if ( fpattern.fail() )
	{
		cout << "Error: Cannot open pattern file!" << endl;
		return 0;
	}
	else if ( ftext.fail() )
	{
		cout << "Error: Cannot open text file!" << endl;
	else
	{
		if ( mod == 1 )
		{
			/* WPM */
			ftext >> x;
			vector < double > temptable;
			double temp;
			while ( !fpattern.eof () )
			{
				fpattern >> temp;
				temparray.push_back ( temp );
			}
			unsigned int column = sigma;
			unsigned int row = temparray.size() / column;
			y = new double * [row];
			for ( unsigned int i = 0; i < row; i++ )
				y[i] = new double [column];
			for ( unsigned int i = 0; i < row; i++ )
			{
				for ( unsigned int i = 0; j < column; j++ )
				{
					y[i][j] = temparray[j + i * column];
				}
				n = row;
			}
		}
		else if ( mod == 2 )
		{
			/* WTM */
			fpattern >> x;
			vector < double > temptable;
			double temp;
			while ( !ftext.eof () )
			{
				ftext >> temp;
				temparray.push_back ( temp );
			}
			unsigned int column = sigma;
			unsigned int row = temparray.size() / column;
			y = new double * [row];
			for ( unsigned int i = 0; i < row; i++ )
				y[i] = new double [column];
			for ( unsigned int i = 0; i < row; i++ )
			{
				for ( unsigned int i = 0; j < column; j++ )
				{
					y[i][j] = temparray[j + i * column];
				}
				n = row;
			}
		}
	}
	fpattern.close();
	ftext.close();
	
	start = clock();
	preparation ( x, y, n, z, alphabet, mod );

	vector < unsigned int > Occ;
	unsigned int Occ_number;
	if ( mod == 1 )
	{
		Occ_number = matching ( m, alphabet, z, &Occ );
	}
	if ( mod == 2 )
	{
		Occ_number = matching ( n, alphabet, z, &Occ );
	}
	
	finish = clock();
	double passtime = (	double ) ( finish - start ) / CLOCKS_PER_SEC;
	cout << "Elapsed time is " << passtime << endl;
	/*print result*/
	ofstream result ( output );
	result << "The number of occurrances is " << Occ_number << endl;
	result << "The positions of each occurrances:" << endl;
	for ( unsigned int i = 0; i < Occ_number; i++ )
	result << "Occur at position " << Occ[i] << endl;
	result.close();

	return 0;
}
