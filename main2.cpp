#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <map>

#include "defs.h"

using namespace std;

int main (int argc, char **argv)
{
	if ( argc == 5 )
	{
		clock_t start, finish;
		unsigned int sigma = strlen( DNA );
		unsigned char * alphabet = new unsigned char [ sigma ];
		memcpy ( alphabet, DNA, sigma );
		double z = 1.0;
		sscanf ( argv[3], "%lf", &z );

		map < string, int > model;
		map < string, int > :: iterator mod;
		model["wpm"] = 1;
		model["wtm"] = 2;

		mod = model.find ( argv[4] );

		ifstream Getlength,FileWeighted;
		ifstream FileString;
		cout << mod->second << endl;
		switch ( mod->second )
		{
			case 1:
				FileWeighted.open ( argv[1] );
				Getlength.open ( argv[1] );
				FileString.open ( argv[2] );
				break;
			case 2:
				FileWeighted.open ( argv[2] );
				Getlength.open ( argv[2] );
				FileString.open ( argv[1] );
				break;
		}
		
		if ( FileWeighted.fail() || FileString.fail() )
			cout << "Cannot open the file" << endl;
		
		Getlength.unsetf ( ios_base::skipws );

		unsigned int m = count( istream_iterator < char > ( Getlength ), istream_iterator < char > (), '\n' );

		Getlength.close();

		double ** x;
		x = new double * [m];
		for ( unsigned int i = 0; i < m; i++ )
			x[i] = new double [sigma];
		for ( unsigned int i = 0; i < m; i++ )
		{
			for ( unsigned int j = 0; j < sigma; j++ )
			{
				FileWeighted >> x[i][j];
			}
		}
		FileWeighted.close();

		for ( unsigned int i = 0; i < m; i++ )
		{
			for ( unsigned int j = 0; j < sigma; j++ )
				cout << x[i][j] << ' ';
			cout << endl;
		}

		string tmp;
		if ( FileString.fail() )
			cout << "Cannot open the file" << endl;
		else
		{
			getline( FileString, tmp );
		}
		unsigned int n = tmp.length();
		unsigned char * y = new unsigned char [ n + 1];
		memcpy ( y, tmp.c_str(), n );
		FileString.close();

		start = clock();
		unsigned int * Occ = new unsigned int [m];
		unsigned int num_Occ;
		switch ( mod->second )
		{
			case 1:
				num_Occ = WPM ( z, alphabet, Occ );
				break;
			case 2:
//				num_Occ = WTM ( y, n, x, m, z, alphabet, Occ );
				break;
		}
		finish = clock();

		double TIME = ( double ) ( finish - start ) / CLOCKS_PER_SEC;
		cout << "The number of Occurrence: " << num_Occ << endl;
		cout << "Elapsed time for processing: " << TIME << endl;
		for ( unsigned int i = 0; i < num_Occ; i++ )
			cout << "x occurs in y at position " << Occ[i] << endl;

		delete[] Occ;
		delete[] y;
		for ( unsigned int i = 0; i < m; i++ )
			delete[] x[i];
		delete[] x;
		delete[] alphabet;
	}
	
	return 0;
}
