#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/locale.hpp>

[[nodiscard]] std::string convert_locale_to_utf(const std::string & string)
{
	boost::locale::generator generator;

	generator.locale_cache_enabled(true);

	const auto locale = generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char > (string, locale);
}

int main()
{
	try
	{
		std::string string; std::cin >> string;

        const std::string u8string = convert_locale_to_utf(string); // note: for Windows cp1251

		std::cout << std::hex << 
            (static_cast < int > (  string[0]) & 0xFF) << ' ' <<
            (static_cast < int > (  string[1]) & 0xFF) << ' ' <<
			(static_cast < int > (u8string[0]) & 0xFF) << ' ' <<
			(static_cast < int > (u8string[1]) & 0xFF) << std::dec << std::endl;

        std::cout <<   string << ' ' <<   string.length() << std::endl;
		std::cout << u8string << ' ' << u8string.length() << std::endl;

		for (const auto c : u8string) std::cout << c << ' ';

		std::cout << std::endl;

	//	std::u16string u16string = 
	//		boost::locale::conv::utf_to_utf < char16_t, char > (u8string);

	//	for (auto c : u16string)
	//	{
	//		std::cout << c << ' ';
	//	}
	//		
	//	std::cout << std::endl;

	//	std::u32string u32string = 
	//		boost::locale::conv::utf_to_utf < char32_t, char > (u8string);
	//	
	//	for (auto c : u32string)
	//	{
	//		std::cout << c << ' ';
	//	}

	//	std::cout << std::endl;

	//	string = boost::locale::conv::utf_to_utf < char, char32_t > (u32string);

	//	std::cout << string << std::endl;

	//	std::u16string u16string_cmp = u"ïðèâåò";

	//	for (auto c : u16string_cmp)
	//	{
	//		std::cout << c << ' ';
	//	}

	//	std::cout << std::endl;

	//	std::cout << std::boolalpha << (u16string == u16string_cmp) << std::endl;

	//	string = u8"ÝÒÎ ÊÎÄÈÐÎÂÊÀ UNICODE UTF-8! \x00AA \x00BB \x00CC \x00DD \x00EE \x00FF";

	//	std::cout << string << ' ' << string.length() << std::endl;

	//	string = convert_utf_to_locale(string);

	//	system("chcp 1251");

	//	std::cout << string << ' ' << string.length() << std::endl;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n';
	}

	return 0;
}