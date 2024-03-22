#include <iostream>
#include <locale>

int main()
{
	std::cout.imbue(std::locale("ru_RU.utf8")); // note: use locale -a to list all installed locales

	for (double value{}; std::cin >> value; ) std::cout << value << std::endl; // note: . -> ,
	
	const std::locale locale_1("en_US.utf8"); 
    
    std::cout.imbue(locale_1);

	std::cout << 1'000'000'000 << std::endl; // note: separator is comma

	std::cout << std::use_facet < std::numpunct < char > > (locale_1).thousands_sep() << std::endl;

	const std::locale locale_2("ru_RU.utf8");

	std::cout.imbue(locale_2);

	std::cout << 1'000'000'000 << std::endl; // note: separator is space

	std::cout << std::use_facet < std::numpunct < char > > (locale_2).thousands_sep() << std::endl;

    return 0;
}