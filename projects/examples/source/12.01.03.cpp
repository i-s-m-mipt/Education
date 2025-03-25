#include <cassert>
#include <chrono>
#include <clocale>
#include <cstring>
#include <ctime>
#include <iostream>
#include <locale>

////////////////////////////////////////////////////////////////////////////////////////////

void test(const std::locale & locale)
{
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	auto timestamp = std::localtime(&time);

	auto format = "%X %x";

//  -----------------------------------------------------------------------------------

	auto previous_locale = std::cout.imbue(locale);

//  -----------------------------------------------------------------------------------

    std::cout << "main : timestamp = ";

	std::use_facet < std::time_put < char > > (locale).put
	(
		std::cout, std::cout, ' ', timestamp, format, format + std::strlen(format)
	);

	std::cout << '\n';

//  -----------------------------------------------------------------------------------

	std::cout.imbue(previous_locale);
}

////////////////////////////////////////////////////////////////////////////////////////////

// support : locale -a

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::locale locale_1("en_US.utf8"); 

    std::locale locale_2("ru_RU.utf8");

//  ----------------------------------------------------------------------------------------

	assert((std::use_facet < std::  numpunct < char > > (locale_1).thousands_sep()) == ',');

    assert((std::use_facet < std::  numpunct < char > > (locale_2).thousands_sep()) == ' ');

	assert((std::use_facet < std::moneypunct < char > > (locale_1).curr_symbol  ()) == "$");

    assert((std::use_facet < std::moneypunct < char > > (locale_2).curr_symbol  ()) == "₽");

//  ----------------------------------------------------------------------------------------

	test(locale_1);

	test(locale_2);

//  ----------------------------------------------------------------------------------------

//	std::setlocale(LC_ALL, "C"); // bad
}