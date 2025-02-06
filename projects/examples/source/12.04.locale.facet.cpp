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

void put_time(const std::locale & locale)
{
	const auto & facet = std::use_facet < std::time_put < char > > (locale);

	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	auto timestamp = std::localtime(&time);

	auto format = "%A %x";

	facet.put(std::cout, std::cout, ' ', timestamp, format, format + std::strlen(format));

	std::cout << '\n';
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() // support: locale -a
{
	{
		std::locale locale("en_US.utf8"); 
    
		std::cout.imbue(locale);

		assert((std::use_facet < std::  numpunct < char > > (locale).thousands_sep()) == ',');

		assert((std::use_facet < std::moneypunct < char > > (locale).curr_symbol  ()) == "$");

		std::cout << "main : date (en_US.utf8) = "; put_time(locale);	
	}
	

//  -----------------------------------------------------------------------------------------------
	
	{
		std::locale locale("ru_RU.utf8");

		std::cout.imbue(locale);

		assert((std::use_facet < std::  numpunct < char > > (locale).thousands_sep()) == ' ');

		assert((std::use_facet < std::moneypunct < char > > (locale).curr_symbol  ()) == "₽");

		std::cout << "main : date (ru_RU.utf8) = "; put_time(locale);
	}

//  -----------------------------------------------------------------------------------------------

	{
		const auto & facet = std::use_facet < std::time_get < char > > (std::locale::classic());

		std::cout << "main : dateorder = std::time_base::";

		switch (auto dateorder = facet.date_order(); dateorder)
		{
			case std::time_base::dmy: { std::cout << "dmy\n"; break; }

			case std::time_base::mdy: { std::cout << "mdy\n"; break; }

			case std::time_base::ymd: { std::cout << "ymd\n"; break; }

			case std::time_base::ydm: { std::cout << "ydm\n"; break; }

			default:
			{
				std::cout << "no_order\n"; break;
			}
		}

		std::cout << "main : enter std::tm (Day MM/DD/YYYY) : ";

		auto state = std::ios_base::goodbit; std::tm tm;

		auto format = "%A %x";

		facet.get
		(
			std::istreambuf_iterator < char > (std::cin), 

			std::istreambuf_iterator < char > (),
			
			std::cin, state, &tm, format, format + std::strlen(format)
		);

		if (state != std::ios_base::goodbit) 
		{
			throw std::runtime_error("invalid format");
		}
	}
}