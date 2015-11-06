#include <iostream>
#include <string>
#include <cstring>
#include <getopt.h>

#include "defs.h"

static struct option long_options[] =
{
	{ "alphabet",			required_argument,	NULL,	'a'	},
	{ "mode",				required_argument,	NULL,	'm' },
	{ "pattern",			required_argument,	NULL,	'p' },
	{ "text",				required_argument,	NULL,	't' },
	{ "output",				required_argument,	NULL,	'o' },
	{ "help",				0,					NULL,	'h' },
};

int decode_switches ( int argc, char * argv[], struct TSwitch * sw )
{
	int opt;
	char *ep;
	int val;
	int args;
	string mod;

	/* initialisation */
	sw -> z						=	1;
	sw -> mod					=	-1;

	args = 0;

	while ( ( opt = getopt_long ( argc, argv, "a:m:p:t:o:z:h", long_options, NULL ) ) != -1 )
	{
		switch ( opt )
		{
			case 'a':
				sw -> alphabet = optarg;
				args ++;
				break;
			case 'm':
				mod = optarg;
				cout << mod << endl;
				if ( optarg == "wpm" )
				{
					sw -> mod = 1;	
				}
				else if ( optarg == "wtm" )
				{
					sw -> mod = 2;
				}
				else
				{
					return 0;
				}
				args ++;
				break;
			case 'p':
				sw -> pattern_file_name = optarg;
				args ++;
				break;
			case 't':
				sw -> text_file_name = optarg;
				args ++;
				break;
			case 'o':
				sw -> output_file_name = optarg;
				args ++;
				break;
			case 'z':
				val = strtol ( optarg, &ep, 10 );
				if ( optarg == ep )
				{
					return 0;
				}
				sw -> z = val;
				args ++;
				break;
			case 'h':
				return 0;
		}
	}

	if ( args < 4 )
	{
		cout << "args < 4" << endl;
		usage();
		exit ( 1 );
	}
	else
		return ( optind );
}

void usage ( void )
{
	cout << "Usage: WPT <options>"  << endl;
	cout << "Standard (Mandatory):" << endl;
	cout << "	-a, --alphabet\t<str>\t'DNA' for nucleotide sequences." << endl;
	cout << "	-m, --mode\t<str>\tchoose the model for program.\n\t 'wpm' for Weighted Pattern Match\n\t'wtm' for Weighted Text Matching" << endl;
	cout << "	-p, --pattern\t<str>\tFilename for Pattern." << endl;
	cout << "	-t, --text\t<str>\tFilename for Text." << endl;
	cout << "	-f, --output\t<str>\tFilename for result output." << endl;
	cout << "	-z\t <dbl>\tcumulative weight threshold."<<endl;
}





