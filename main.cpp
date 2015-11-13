#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#include "defs.h"

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
	unsigned int num_Occ;
	vector < unsigned int > Occ;
	unsigned int column;
	unsigned int row;

	clock_t start, finish;

	unsigned int k;

	/* Decodes the arguments */
	k = decode_switches ( argc, argv, &sw );

	/* Check the arguments */
	if ( k < 7 )
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

		if ( sw.output_file_name.size() == 0 )
		{
			output = "MatchingReport";		
		}
		else
		{
			output = sw.output_file_name;
		}

		if ( sw.z > 0 )
		{
			z = sw.z;
		}
		else 
		{
			cout << "Error: z must be a position integer!" << endl;
		}
	}
	/* read input Weighted String */
	ifstream fpattern ( pattern_file );
	ifstream ftext ( text_file );
	if ( fpattern.fail() )
	{
		cout << "Error: Cannot open pattern file!" << endl;
		return 0;
	}
	else if ( ftext.fail() )
	{
		cout << "Error: Cannot open text file!" << endl;
	}
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
				temptable.push_back ( temp );
			}
			column = sigma;
			row = temptable.size() / column;
			y = new double * [row];
			for ( unsigned int i = 0; i < row; i++ )
				y[i] = new double [column];
			for ( unsigned int i = 0; i < row; i++ )
			{
				for ( unsigned int j = 0; j < column; j++ )
				{
					y[i][j] = temptable[j + i * column];
				}
			}
			n = row;
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
				temptable.push_back ( temp );
			}
			column = sigma;
			row = temptable.size() / column;
			y = new double * [row];
			for ( unsigned int i = 0; i < row; i++ )
				y[i] = new double [column];
			for ( unsigned int i = 0; i < row; i++ )
			{
				for ( unsigned int j = 0; j < column; j++ )
				{
					y[i][j] = temptable[j + i * column];
				}
			}
			n = row;
		}
	}
	fpattern.close();
	ftext.close();

	start = clock();
	preparation ( x, y, n, z, alphabet, mod );

	switch ( mod )
	{
		case 1:
			num_Occ = WPM ( z, alphabet, &Occ );
			break;
		case 2:
			num_Occ = WTM ( z, alphabet, &Occ );
			break;
	}
	finish = clock();

	double passtime = ( ( double ) finish - start ) / CLOCKS_PER_SEC;

	for ( unsigned int i = 0; i < num_Occ; i++ )
	{
		cout << "Pattern occurs at position:" << Occ[i] << endl;
	}

	cout << "time: " << passtime << "s" << endl;

	for ( unsigned int i = 0; i < row; i++ )
		delete[] y[i];
	delete[] y;

	return 0;
}
