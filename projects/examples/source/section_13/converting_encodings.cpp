#include <bit>
#include <codecvt>
#include <exception>
#include <iomanip>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/locale.hpp>

//#include <Windows.h> // note: required on Windows for changing code page

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

[[nodiscard]] inline std::string convert_wstring_to_utf8(const std::wstring & wstring)
{
	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter; // note: deprecated, bad implementation

	return converter.to_bytes(wstring);
}

[[nodiscard]] inline std::wstring convert_utf8_to_wstring(const std::string & string)
{
	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter; // note: deprecated, bad implementation

	return converter.from_bytes(string);
}

[[nodiscard]] inline std::wstring convert_string_to_wstring(const std::string & string, const std::locale & locale) 
{
	std::vector < wchar_t > buffer(std::size(string));

	std::use_facet < std::ctype < wchar_t > >(locale).widen(
		string.data(), 
		string.data() + std::size(string), buffer.data());

	return std::wstring(buffer.data(), std::size(buffer)); // note: avoid wchar_t and std::wstring
}

[[nodiscard]] inline std::string convert_wstring_to_string(const std::wstring & wstring, const std::locale & locale) 
{
	std::vector < char > buffer(std::size(wstring));

	std::use_facet < std::ctype < wchar_t > > (locale).narrow(
		wstring.data(),
		wstring.data() + std::size(wstring), '?', buffer.data()); // note: default character

	return std::string(buffer.data(), std::size(buffer)); // note: avoid wchar_t and std::wstring
}

int main()
{
    std::cout << boost::locale::util::get_system_locale() << std::endl;

	std::string string; std::cin >> string; // note: can be not UTF-8

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