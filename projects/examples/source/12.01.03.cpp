////////////////////////////////////////////////////////////////////////////////////////////

// support : locale -a

////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cstring>
#include <ctime>
#include <locale>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::locale locale_1("en_US.utf8"); 

    std::locale locale_2("ru_RU.utf8");

//  ----------------------------------------------------------------------------------------

	assert((std::use_facet < std::  numpunct < char > > (locale_1).thousands_sep()) == ',');

    assert((std::use_facet < std::  numpunct < char > > (locale_2).thousands_sep()) == ' ');

//  ----------------------------------------------------------------------------------------

	assert((std::use_facet < std::moneypunct < char > > (locale_1).curr_symbol  ()) == "$");

    assert((std::use_facet < std::moneypunct < char > > (locale_2).curr_symbol  ()) == "₽");

//  ----------------------------------------------------------------------------------------

	assert(make_timestamp(locale_1) == "12:00:00 AM 01/01/1970");

	assert(make_timestamp(locale_2) == "00:00:00 01.01.1970"   );
}

////////////////////////////////////////////////////////////////////////////////////////////