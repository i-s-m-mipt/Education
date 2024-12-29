#include <cassert>
#include <chrono>
#include <cstring>
#include <ctime>
#include <exception>
#include <ios>
#include <iostream>
#include <iterator>
#include <locale>
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() // support: locale -a
{
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	auto date = std::localtime(&time);

	auto format = "%A %x";

//  -----------------------------------------------------------------------------------------------
	
	std::locale locale_1("en_US.utf8"); 
    
    std::cout.imbue(locale_1);

	assert((std::use_facet < std::  numpunct < char        > > (locale_1).thousands_sep()) == ',');

	assert((std::use_facet < std::moneypunct < char, false > > (locale_1).curr_symbol  ()) == "$");

	const auto & time_put_1 = std::use_facet < std::time_put < char > > (locale_1);

	std::cout << "main : date (en_US.utf8) = ";

	time_put_1.put(std::cout, std::cout, ' ', date, format, format + std::strlen(format));

	std::cout << '\n';

//  -----------------------------------------------------------------------------------------------

	std::locale locale_2("ru_RU.utf8");

	std::cout.imbue(locale_2);

	assert((std::use_facet < std::  numpunct < char        > > (locale_2).thousands_sep()) == ' ');

	assert((std::use_facet < std::moneypunct < char, false > > (locale_2).curr_symbol  ()) == "₽");

	const auto & time_put_2 = std::use_facet < std::time_put < char > > (locale_2);

	std::cout << "main : date (ru_RU.utf8) = ";

	time_put_2.put(std::cout, std::cout, ' ', date, format, format + std::strlen(format));

	std::cout << '\n';

//  -----------------------------------------------------------------------------------------------

	const auto & time_get_C = std::use_facet < std::time_get < char > > (std::locale::classic());

	switch (std::cout << "main : time_get_C.date_order() = "; time_get_C.date_order())
	{
		case std::time_base::dmy: { std::cout << "dmy\n"; break; }
		case std::time_base::mdy: { std::cout << "mdy\n"; break; }
		case std::time_base::ymd: { std::cout << "ymd\n"; break; }
		case std::time_base::ydm: { std::cout << "ydm\n"; break; }

		default:
		{
			std::cout << "unknown\n"; break;
		}
	}

	std::cout << "main : enter std::tm (Day MM/DD/YYYY) : ";

	auto state = std::ios_base::goodbit; std::tm input;

	time_get_C.get
	(
		std::istreambuf_iterator < char > (std::cin), 
		std::istreambuf_iterator < char > (        ),
		
		std::cin, state, &input, format, format + std::strlen(format)
	);

	if (state != std::ios_base::goodbit) 
	{
		throw std::runtime_error("invalid data");
	}
}