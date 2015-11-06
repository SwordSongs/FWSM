#include <vector>
#include <string>

using namespace std;

#define ALLOC_SIZE               10000
#define DNA "ACGT"
#define dna "acgt"

#ifndef TSWITCH_H
#define TSWITCH_H
struct TSwitch
{
	int		mod;
	double	z;
	string	pattern_file_name;
	string	text_file_name;
	string	output_file_name;
	string	alphabet;
};
#endif

#ifndef STRINGS_H
#define STRINGS_H
struct STRINGS
{
	vector < unsigned int > pattern;
	vector < unsigned int > text;
	vector < unsigned int > BP;
	vector < double >		prob;
	vector < vector < double > > bptable;
};
#endif

#ifndef FACTOR_H
#define FACTOR_H
struct Factor
{
	unsigned int *	str;					//the string of factor
	unsigned int	length;					//the length of factor
	unsigned int	start;					//the start position of factor
	unsigned int	end;					//the end position of factor
	double			prob;					//the probability of factor
};
#endif

int decode_switches ( int argc, char * argv[], struct TSwitch * sw );
void usage ( void );
void preparation ( string x, double **y, unsigned int n, double z, string alphabet, int mod );
void KMP ( unsigned int * x, unsigned int m, unsigned int * y, unsigned int n, vector < unsigned int > * Occ );
unsigned int WPM ( double z, string alphabet, vector < unsigned int > * Occ );
unsigned int WTM ( double z, string alphabet, vector < unsigned int > * Occ );
void fragments ( int i, int j, int f, unsigned int m, int * mf, int * ind );
unsigned int extract_dups_single_str ( unsigned char * xx, unsigned int m, unsigned int f, int * mf, int * ind, int * dups );
