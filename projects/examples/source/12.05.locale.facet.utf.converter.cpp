#include <cassert>
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std::literals;

#include <boost/locale.hpp>

//////////////////////////////////////////////////////////////////////////////////////

auto convert_v1(const std::string & string)
{
	boost::locale::generator generator;

	generator.locale_cache_enabled(true);

	auto locale = generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char > (string, locale);
}

//////////////////////////////////////////////////////////////////////////////////////

auto convert_v2(const std::string & string)
{
	boost::locale::generator generator; 
    
    generator.locale_cache_enabled(true);

	auto locale = generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char > (string, locale);
}

//////////////////////////////////////////////////////////////////////////////////////

auto convert_v3(std::string_view view, const std::locale & locale) 
{
	std::vector < wchar_t > vector(std::size(view), L'\0');

	std::use_facet < std::ctype < wchar_t > > (locale).widen
    (
		std::data(view), 
        
        std::data(view) + std::size(view), std::data(vector)
    );

	return std::wstring(std::data(vector), std::size(vector));
}

//////////////////////////////////////////////////////////////////////////////////////

auto convert_v4(std::wstring_view view, const std::locale & locale)
{
	std::vector < char > vector(std::size(view), '\0');

	std::use_facet < std::ctype < wchar_t > > (locale).narrow
    (
		std::data(view),
        
		std::data(view) + std::size(view), '?', std::data(vector)
    );

	return std::string(std::data(vector), std::size(vector));
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        auto locale = boost::locale::util::get_system_locale();

        std::cout << "main : locale = " << locale << '\n';
    }
    
//  ----------------------------------------------------------------------------------

    {
        auto string_1 = "ааааа"s; auto size = std::size(string_1);

        std::cout << "main : size = " << size << '\n';

        auto string_2 = convert_v1(string_1);

        assert(std::size(string_2) == 10);

        assert(((string_2[0] & 0xff) << 8 | (string_2[1] & 0xff)) == 53'424);

        auto string_3 = boost::locale::conv::utf_to_utf < char32_t, char > (string_2);

        assert(std::size(string_3) == 5 && string_3.front() == 1'072);

        string_2 = boost::locale::conv::utf_to_utf < char, char32_t > (string_3);

	    assert(convert_v2(string_2) == string_1);
    }

//  ----------------------------------------------------------------------------------

    {
        std::unordered_map < char32_t, std::u32string > map = 
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
    }
}