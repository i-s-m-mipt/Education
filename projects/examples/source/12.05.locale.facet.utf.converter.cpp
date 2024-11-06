#include <bit>
#include <codecvt>
#include <exception>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <boost/locale.hpp>

//  ================================================================================================

auto convert_v1(const std::string & string)
{
	boost::locale::generator generator;

	generator.locale_cache_enabled(true);

	auto locale = generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char > (string, locale);
}

auto convert_v2(const std::string & string)
{
	boost::locale::generator generator;

	generator.locale_cache_enabled(true);

	auto locale = generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char > (string, locale);
}

//  ================================================================================================

template < typename S > void print(const S & string)
{
    for (auto element : string) 
    { 
        std::cout << static_cast < int > (element) << ' '; 
    }

    std::cout << '\n';
}

//  ================================================================================================

//  auto convert_v3(const std::wstring & wstring)
//  {
//  	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter; // bad
//
//  	return converter.to_bytes(wstring);
//  }

//  auto convert_v4(const std::string & string)
//  {
//  	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter; // bad
//
//  	return converter.from_bytes(string);
//  }

//  ================================================================================================

auto convert_v5(std::string_view string, const std::locale & locale) 
{
	std::vector < wchar_t > buffer(std::size(string), L'\0');

	std::use_facet < std::ctype < wchar_t > > (locale).widen
    (
		std::data(string), 
		std::data(string) + std::size(string), std::data(buffer)
    );

	return std::wstring(std::data(buffer), std::size(buffer));
}

//  --------------------------------------------------------------------------------

auto convert_v6(std::wstring_view wstring, const std::locale & locale)
{
	std::vector < char > buffer(std::size(wstring), '\0');

	std::use_facet < std::ctype < wchar_t > > (locale).narrow
    (
		std::data(wstring),
		std::data(wstring) + std::size(wstring), '?', std::data(buffer)
    );

	return std::string(std::data(buffer), std::size(buffer));
}

//  ================================================================================================

const auto & transliteration() 
{
    static std::unordered_map < char32_t, std::u32string > table
    { 
        { U'А', U"A"   }, { U'а', U"a"   },
        { U'Б', U"B"   }, { U'б', U"b"   },
        { U'В', U"V"   }, { U'в', U"v"   },
        { U'Г', U"G"   }, { U'г', U"g"   },
        { U'Д', U"D"   }, { U'д', U"d"   },
        { U'Е', U"E"   }, { U'е', U"e"   },
        { U'Ё', U"Yo"  }, { U'ё', U"yo"  },
        { U'Ж', U"Zh"  }, { U'ж', U"zh"  },
        { U'З', U"Z"   }, { U'з', U"z"   },
        { U'И', U"I"   }, { U'и', U"i"   },
        { U'Й', U"J"   }, { U'й', U"j"   },
        { U'К', U"K"   }, { U'к', U"k"   },
        { U'Л', U"L"   }, { U'л', U"l"   },
        { U'М', U"M"   }, { U'м', U"m"   },
        { U'Н', U"N"   }, { U'н', U"n"   },
        { U'О', U"O"   }, { U'о', U"o"   },
        { U'П', U"P"   }, { U'п', U"p"   },
        { U'Р', U"R"   }, { U'р', U"r"   },
        { U'С', U"S"   }, { U'с', U"s"   },
        { U'Т', U"T"   }, { U'т', U"t"   },
        { U'У', U"U"   }, { U'у', U"u"   },
        { U'Ф', U"Ph"  }, { U'ф', U"ph"  },
        { U'Х', U"H"   }, { U'х', U"h"   },
        { U'Ц', U"Ts"  }, { U'ц', U"ts"  },
        { U'Ч', U"Ch"  }, { U'ч', U"ch"  },
        { U'Ш', U"Sh"  }, { U'ш', U"sh"  },
        { U'Щ', U"Sch" }, { U'щ', U"sch" },
        { U'Ы', U"I"   }, { U'ы', U"i"   },
        { U'ъ', U""    }, { U'ь', U"'"   },
        { U'Э', U"E"   }, { U'э', U"e"   },
        { U'Ю', U"Yu"  }, { U'ю', U"yu"  },
        { U'Я', U"Ya"  }, { U'я', U"ya"  } 
	};

    return table;
}

//  ================================================================================================

int main()
{
    std::cout << boost::locale::util::get_system_locale() << std::endl;

	std::cout << "Enter 1 string : "; std::string string; std::cin >> string;

    auto u8string = convert_v1(string);

//  ================================================================================================

    std::cout << std::hex;

	std::cout << (static_cast < int > (  string[0]) & 0xFF) << ' ';
    std::cout << (static_cast < int > (  string[1]) & 0xFF) << ' ';
	std::cout << (static_cast < int > (u8string[0]) & 0xFF) << ' ';
	std::cout << (static_cast < int > (u8string[1]) & 0xFF) << std::endl;

    std::cout << std::dec;

    std::cout <<   string << ' ' << std::size(  string) << std::endl;
    std::cout << u8string << ' ' << std::size(u8string) << std::endl;

//  ================================================================================================

    auto u16string = boost::locale::conv::utf_to_utf < char16_t, char > (u8string);
    auto u32string = boost::locale::conv::utf_to_utf < char32_t, char > (u8string);

	print( u8string);
	print(u16string);
	print(u32string);

//  ================================================================================================

	u8string = boost::locale::conv::utf_to_utf < char, char32_t > (u32string);

	std::cout << convert_v2(u8string) << std::endl;

//  ================================================================================================

	std::cout << convert_v2("∃y ∀x ¬(x ≺ y)") << std::endl;
}