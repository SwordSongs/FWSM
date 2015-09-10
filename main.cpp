#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#include "defs.h"

using namespace std;

int main (int argc, char **argv)
{
	if ( argc == 4 )
	{
		unsigned int m = 0;
		unsigned int sigma = strlen( DNA );
		unsigned char * alphabet = new unsigned char [ sigma ];
		memcpy ( alphabet, DNA, sigma );
		double z = 1.0;
		sscanf ( argv[3], "%lf", &z );

		ifstream ReadX;
		string tmp1;
		ReadX.open ( argv[1] );
		if ( ReadX.fail() )
			cout << "Cannot open the file" << endl;
		else
		{
			while ( getline ( ReadX, tmp1, '\n' ) )
				m++;
		}
		ReadX.close();

		ifstream in ( argv[1] );
		double ** x;
		x = new double * [m];
		for ( unsigned int i = 0; i < m; i++ )
			x[i] = new double [sigma];
		for ( unsigned int i = 0; i < m; i++ )
		{
			for ( unsigned int j = 0; j < sigma; j++ )
			{
				in >> x[i][j];
			}
		}
		in.close();

		ifstream ReadY;
		ReadY.open ( argv[2] );
		string tmp2;
		if ( ReadY.fail() )
			cout << "Cannot open the file" << endl;
		else
		{
			getline( ReadY, tmp2 );
		}
		unsigned int n = tmp2.length();
		unsigned char * y = new unsigned char [ n + 1];
		memcpy ( y, tmp2.c_str(), n );
		ReadY.close();

		unsigned int * Occ = new unsigned int [m];
		unsigned int num_Occ;
		num_Occ = WMP ( x, m, y, n, z, alphabet, Occ );
		cout << "The number of Occurrence: " << num_Occ << endl;
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
