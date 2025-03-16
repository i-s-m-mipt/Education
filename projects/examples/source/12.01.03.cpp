#include <cassert>
#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>
#include <locale>

////////////////////////////////////////////////////////////////////////////////////////////

void put_time(const std::locale & locale)
{
	const auto & facet = std::use_facet < std::time_put < char > > (locale);

	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	auto timestamp = std::localtime(&time);

	auto format = "%X %x";

//  --------------------------------------------------------------------------------------

    std::cout << "main : timestamp = ";

    std::cout.imbue(locale);

	facet.put(std::cout, std::cout, ' ', timestamp, format, format + std::strlen(format));

	std::cout << '\n';
}

////////////////////////////////////////////////////////////////////////////////////////////

int main() // support: locale -a
{
	std::locale locale_1("en_US.utf8");

    std::locale locale_2("ru_RU.utf8");

//  ----------------------------------------------------------------------------------------

	assert((std::use_facet < std::  numpunct < char > > (locale_1).thousands_sep()) == ',');

    assert((std::use_facet < std::  numpunct < char > > (locale_2).thousands_sep()) == ' ');

	assert((std::use_facet < std::moneypunct < char > > (locale_1).curr_symbol  ()) == "$");

    assert((std::use_facet < std::moneypunct < char > > (locale_2).curr_symbol  ()) == "₽");

//  ----------------------------------------------------------------------------------------

	put_time(locale_1);

    put_time(locale_2);
}