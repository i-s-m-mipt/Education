/////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <locale>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/locale.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////

auto make_string_v1(std::string const & string, std::locale const & locale) 
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

/////////////////////////////////////////////////////////////////////////////////////////////////

auto make_string_v2(std::wstring const & wstring, std::locale const & locale)
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

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto locale = boost::locale::generator()(boost::locale::util::get_system_locale());

//  ---------------------------------------------------------------------------------------------

    assert(make_string_v1( "aaaaa", locale) == L"aaaaa");

    assert(make_string_v2(L"aaaaa", locale) ==  "aaaaa");

//  ---------------------------------------------------------------------------------------------

    auto method = boost::locale::conv::method_type::skip;

//  ---------------------------------------------------------------------------------------------

    auto string_1 = "ааааа"s;

//  ---------------------------------------------------------------------------------------------

    auto string_2 = boost::locale::conv::         to_utf < char     > (string_1, locale, method);

    auto string_3 = boost::locale::conv::     utf_to_utf < char32_t > (string_2,         method);

    auto string_4 = boost::locale::conv::     utf_to_utf < char     > (string_3,         method);

    auto string_5 = boost::locale::conv::from_utf        < char     > (string_4, locale, method);

//  ---------------------------------------------------------------------------------------------

    assert(std::size(string_2) == 2 * 5 && string_2 ==  "ааааа");

    assert(std::size(string_3) == 1 * 5 && string_3 == U"ааааа");

//  ---------------------------------------------------------------------------------------------

    assert(string_4 == string_2);

	assert(string_5 == string_1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////