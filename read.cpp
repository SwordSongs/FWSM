#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>


int main ( int argc, char ** argv )
{
	if ( argc == 2 )
	{
		    std::ifstream myfile( argv[1] );

			    // new lines will be skipped unless we stop it from happening:    
 myfile.unsetf(std::ios_base::skipws);
				    // count the newlines with an algorithm specialized for counting:
				    unsigned int line_count = std::count(
							        std::istream_iterator<char>(myfile),
									        std::istream_iterator<char>(), 
											        '\n');

					    std::cout << "Lines: " << line_count << "\n";
						    return 0;
	}
	return 0;
}

