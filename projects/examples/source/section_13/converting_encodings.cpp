#include <exception>
#include <iomanip>
#include <iostream>
#include <ostream>
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

[[nodiscard]] std::string convert_utf_to_locale(const std::string & string)
{
	boost::locale::generator generator;

	generator.locale_cache_enabled(true);

	const auto locale = generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char > (string, locale);
}

int main()
{
    std::cout << boost::locale::util::get_system_locale() << std::endl;

	std::string string; std::cin >> string; // note: can be not UTF-8, cp1251 on Windows

    auto u8string = convert_locale_to_utf(string);

	std::cout << std::hex << 
        (static_cast < int > (  string[0]) & 0xFF) << ' ' <<
        (static_cast < int > (  string[1]) & 0xFF) << ' ' <<
		(static_cast < int > (u8string[0]) & 0xFF) << ' ' <<
		(static_cast < int > (u8string[1]) & 0xFF) << std::dec << std::endl;

    std::cout <<   string << ' ' <<   string.length() << std::endl;
    std::cout << u8string << ' ' << u8string.length() << std::endl;

    const auto u16string = boost::locale::conv::utf_to_utf < char16_t, char > (u8string);
    const auto u32string = boost::locale::conv::utf_to_utf < char32_t, char > (u8string);

//  SetConsoleOutputCP(65001); // note: Windows only, change console code page to UTF-8

	for (const auto c :  u8string) std::cout << static_cast < int > (c) << ' '; // note: no support

	std::cout << std::endl;

	for (const auto c : u16string) std::cout << static_cast < int > (c) << ' '; // note: no support
			
	std::cout << std::endl;

	for (const auto c : u32string) std::cout << static_cast < int > (c) << ' '; // note: no support

	std::cout << std::endl;

	u8string = boost::locale::conv::utf_to_utf < char, char32_t > (u32string);

	std::cout << convert_utf_to_locale(u8string) << std::endl;

	std::cout << convert_utf_to_locale("∃y ∀x ¬(x ≺ y)") << std::endl; // note: problem with char8_t 

	return 0;
}