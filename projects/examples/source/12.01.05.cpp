#include <cassert>
#include <locale>
#include <string>
#include <vector>

using namespace std::literals;

#include <boost/locale.hpp>

///////////////////////////////////////////////////////////////////////////////////////

auto convert_v1(const std::string & string, const std::locale & locale) 
{
    auto size = std::size(string);

	std::vector < wchar_t > vector(size, L'\0');

	std::use_facet < std::ctype < wchar_t > > (locale).widen
    (
		std::data(string), 
        
        std::data(string) + size, std::data(vector)
    );

	return std::wstring(std::data(vector), size);
}

///////////////////////////////////////////////////////////////////////////////////////

auto convert_v2(const std::wstring & wstring, const std::locale & locale)
{
    auto size = std::size(wstring);

	std::vector < char > vector(size, '\0');

	std::use_facet < std::ctype < wchar_t > > (locale).narrow
    (
		std::data(wstring),
        
		std::data(wstring) + size, '?', std::data(vector)
    );

	return std::string(std::data(vector), size);
}

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto locale = boost::locale::generator()(boost::locale::util::get_system_locale());

//  -----------------------------------------------------------------------------------

    auto string_1 = "ааааа"s;

    auto string_2 = boost::locale::conv::to_utf < char > (string_1, locale);

//  -----------------------------------------------------------------------------------

    assert(std::size(string_1) == 10);

    assert(std::size(string_2) == 10);

//  -----------------------------------------------------------------------------------

    auto string_3 = boost::locale::conv::utf_to_utf < char32_t, char > (string_2);

    auto string_4 = boost::locale::conv::utf_to_utf < char, char32_t > (string_3);

//  -----------------------------------------------------------------------------------

    assert(std::size(string_3) == 5 && string_3.front() == U'а');

//  -----------------------------------------------------------------------------------

	auto string_5 = boost::locale::conv::from_utf < char > (string_4, locale);

//  -----------------------------------------------------------------------------------

    assert(string_4 == string_2);

	assert(string_5 == string_1);

//  -----------------------------------------------------------------------------------

    assert(convert_v2(convert_v1("aaaaa"s, locale), locale) == "aaaaa"s);
}