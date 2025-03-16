#include <cassert>
#include <ctime>
#include <iomanip>
#include <locale>
#include <sstream>

////////////////////////////////////////////////////

int main()
{
	std::stringstream stream("00:00:00 01/01/1970");

//  ------------------------------------------------

	stream.imbue(std::locale());

//  ------------------------------------------------

	std::tm tm;

//  ------------------------------------------------
	
	stream >> std::get_time(&tm, "%X %x");

//  ------------------------------------------------

	assert(timegm(&tm) == 0);	
}