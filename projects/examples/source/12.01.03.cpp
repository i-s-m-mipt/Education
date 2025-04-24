////////////////////////////////////////////////////////////////////////////////////////////

// support : locale -a

////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <clocale>
#include <cstring>
#include <ctime>
#include <iostream>
#include <locale>

////////////////////////////////////////////////////////////////////////////////////////////

void put_time(std::locale const & locale_1)
{
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	auto timestamp = std::localtime(&time);

	auto format = "%X %x";

	auto locale_2 = std::cout.imbue(locale_1);

    std::cout << "main : timestamp = ";

	std::use_facet < std::time_put < char > > (locale_1).put
	(
		std::cout, std::cout, ' ', timestamp, format, format + std::strlen(format)
	);

	std::cout << '\n';

	std::cout.imbue(locale_2);
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

	put_time(locale_1);

	put_time(locale_2);
}

////////////////////////////////////////////////////////////////////////////////////////////