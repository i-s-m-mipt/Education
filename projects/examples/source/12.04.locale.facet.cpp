#include <chrono>
#include <cstring>
#include <ctime>
#include <exception>
#include <ios>
#include <iostream>
#include <iterator>
#include <locale>
#include <stdexcept>

int main() // support: locale -a
{
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	auto data = std::localtime(&time);

	auto format = "%A %x";

//  ================================================================================================
	
	std::locale locale_1("en_US.utf8"); 
    
    std::cout.imbue(locale_1);

	std::cout << 1'000'000'000 << std::endl;

	std::cout << std::use_facet < std::numpunct   < char        > > (locale_1).thousands_sep();
	std::cout << std::use_facet < std::moneypunct < char, false > > (locale_1).curr_symbol  ();

	std::cout << std::endl;

	const auto & time_put_1 = std::use_facet < std::time_put < char > > (locale_1);

	time_put_1.put(std::cout, std::cout, ' ', data, format, format + std::strlen(format));

	std::cout << std::endl;

//  ================================================================================================

	std::locale locale_2("ru_RU.utf8");

	std::cout.imbue(locale_2);

	std::cout << 1'000'000'000 << std::endl;

	std::cout << std::use_facet < std::numpunct   < char        > > (locale_2).thousands_sep();
	std::cout << std::use_facet < std::moneypunct < char, false > > (locale_2).curr_symbol  ();

	std::cout << std::endl;

	const auto & time_put_2 = std::use_facet < std::time_put < char > > (locale_2);

	time_put_2.put(std::cout, std::cout, ' ', data, format, format + std::strlen(format));

	std::cout << std::endl;

//  ================================================================================================

	const auto & time_get_C = std::use_facet < std::time_get < char > > (std::locale::classic());

	auto dateorder = time_get_C.date_order();

	std::cout << "dateorder : "
			  << (dateorder == std::time_base::no_order || 
			      dateorder == std::time_base::mdy ? "mdy" :
				  dateorder == std::time_base::dmy ? "dmy" :
				  dateorder == std::time_base::ymd ? "ymd" :
				  dateorder == std::time_base::ydm ? "ydm" : "unknown") << '\n';

	std::cout << "Enter 1 date (Day MM/DD/YYYY) : ";

	auto state = std::ios_base::goodbit; tm input;

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