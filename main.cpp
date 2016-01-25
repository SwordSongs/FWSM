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
	ofstream result;

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
	alphabet = DNA;
	sigma = alphabet.size();
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
			double temp;
			long int num_pattern = 0;
			while ( !fpattern.eof () )
			{
				fpattern >> temp;
				num_pattern ++;
			}
			fpattern.clear();
			fpattern.seekg( 0, ios::beg );
			column = sigma;
			row = num_pattern / column;
			y = new double * [row];
			for ( unsigned int i = 0; i < row; i++ )
				y[i] = new double [column];
			for ( unsigned int i = 0; i < row; i++ )
			{
				for ( unsigned int j = 0; j < column; j++ )
				{
					fpattern >> y[i][j];
				}
			}
			n = row;
		}
		else if ( mod == 2 )
		{
			/* WTM */
			fpattern >> x;
			double temp;
			long int num_text = 0;
			while ( !ftext.eof () )
			{
				ftext >> temp;
				num_text ++;
			}
			ftext.clear();
			ftext.seekg( 0, ios::beg );
			column = sigma;
			row = num_text / column;
			y = new double * [row];
			for ( unsigned int i = 0; i < row; i++ )
				y[i] = new double [column];
			for ( unsigned int i = 0; i < row; i++ )
			{
				for ( unsigned int j = 0; j < column; j++ )
				{
					ftext >> y[i][j];
				}
			}
			n = row;
		}
	}
	fpattern.close();
	ftext.close();

	start = clock();

	m = x.length();
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
	
	cout << "Number of Occurrences: " << num_Occ << endl;
	cout << "time: " << passtime << "s" << endl;

#if 1
	result.open ( output );
	if ( num_Occ == 0 )
	{
		result << "No Occurrences is found.\n";
	}
	else
	{
		result << "Positions of Occurrences:\n";
		for ( unsigned int i = 0; i < num_Occ; i++ )
			result << Occ[i] << '\n';
	}
#endif

#if 0
	result.open ( "wsm.dat", ios::app );
	if ( mod == 1 )
		result << n << "\t" << passtime << endl;
	if ( mod == 2 )
		result << m << "\t" << passtime << endl;
	result.close();
#endif

	for ( unsigned int i = 0; i < row; i++ )
		delete[] y[i];
	delete[] y;

	return 0;
}
