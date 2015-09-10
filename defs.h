#define DNA "ACGT"

struct Factor
{
	unsigned char *	str;					//the string of factor
	unsigned int	length;					//the length of factor
	unsigned int	start;					//the start position of factor
	unsigned int	end;					//the end position of factor
	double			prob;					//the probability of factor
};

unsigned int WMP ( double ** x, unsigned int m, unsigned char * y, unsigned int n, double z, unsigned char * alphabet, unsigned int * Occ );
