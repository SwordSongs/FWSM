#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#include "defs.h"

using namespace std;

int main (int argc, char **argv)
{
	cout << "123" << endl;
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

	unsigned int k;

	/* Decodes the arguments */
//	k = decode_switches ( argc, argv, &sw );

	/* Check the arguments */
/*	if ( k < 0 )
	{
		cout << "k = " << k  << endl;
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

		if ( z > 0 )
		{
			z = sw.z;
		}
		else 
		{
			cout << "Error: z must be a position integer!" << endl;
		}
	}
*/
	/* read input Weighted String */
	ifstream fpattern ( "pattern" );
	ifstream ftext ( "text" );
	alphabet = DNA;
	sigma = alphabet.size();
	mod = 2;
	z = 88888888;
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
			unsigned int column = sigma;
			cout << column;
			unsigned int row = temptable.size() / column;
			y = new double * [row];
			for ( unsigned int i = 0; i < row; i++ )
				y[i] = new double [column];
			for ( unsigned int i = 0; i < row; i++ )
			{
				for ( unsigned int j = 0; j < column; j++ )
				{
					y[i][j] = temptable[j + i * column];
				}
				n = row;
			}
		}
		else if ( mod == 2 )
		{
			cout << mod << endl;
			/* WTM */
			fpattern >> x;
			vector < double > temptable;
			double temp;
			while ( !ftext.eof () )
			{
				ftext >> temp;
				temptable.push_back ( temp );
			}
			unsigned int column = sigma;
			unsigned int row = temptable.size() / column;
			y = new double * [row];
			for ( unsigned int i = 0; i < row; i++ )
				y[i] = new double [column];
			for ( unsigned int i = 0; i < row; i++ )
			{
				for ( unsigned int j = 0; j < column; j++ )
				{
					y[i][j] = temptable[j + i * column];
				}
				n = row;
			}
		}
	}
	fpattern.close();
	ftext.close();
	cout << "!£" << endl;
	preparation ( x, y, n, z, alphabet, mod );
	cout << "455" << endl;

	switch ( mod )
	{
		case 1:
			num_Occ = WPM ( z, alphabet, &Occ );
			break;
		case 2:
			num_Occ = WTM ( z, alphabet, &Occ );
			break;
	}

	for ( unsigned int i = 0; i < num_Occ; i++ )
	{
		cout << Occ[i] << endl;
	}

	return 0;
}
