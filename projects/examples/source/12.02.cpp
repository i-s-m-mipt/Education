////////////////////////////////////////////////////////////////////////////

// chapter : Characters

////////////////////////////////////////////////////////////////////////////

// section : Locales

////////////////////////////////////////////////////////////////////////////

// content : Type Alias std::time_t
//
// content : Imbuing Locales
//
// content : Function std::gmtime
//
// content : Facet std::time_put
//
// content : Function std::strlen
//
// content : Time std::tm
//
// content : Function std::get_time
//
// content : Function timegm

////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <locale>
#include <sstream>

////////////////////////////////////////////////////////////////////////////

auto make_timestamp(std::locale const & locale, std::time_t time = 0)
{
	std::stringstream stream;

	stream.imbue(locale);

	auto timestamp = std::gmtime(&time);

	auto format = "%X %x";

	std::use_facet < std::time_put < char > > (locale).put
	(
		stream, stream, ' ', timestamp, format, format + std::strlen(format)
	);

	return stream.str();
}

////////////////////////////////////////////////////////////////////////////

int main()
{
    std::locale locale("ru_RU.utf8");

//  -------------------------------------------------

	std::stringstream stream(make_timestamp(locale));

//  -------------------------------------------------

	stream.imbue(locale);

//  -------------------------------------------------

	std::tm tm;

//  -------------------------------------------------

	stream >> std::get_time(&tm, "%X %x");

//  -------------------------------------------------

	assert(timegm(&tm) == 0);

//  -------------------------------------------------

	assert(stream.str() == "00:00:00 01.01.1970");
}

////////////////////////////////////////////////////////////////////////////