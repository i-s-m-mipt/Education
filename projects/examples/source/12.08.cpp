///////////////////////////////////////////////////////////////////////////////////////

// chapter : Text Processing

///////////////////////////////////////////////////////////////////////////////////////

// section : Strings

///////////////////////////////////////////////////////////////////////////////////////

// content : String std::basic_string
//
// content : User-Defined Case-Insensitive Strings
//
// content : Utility std::char_traits
//
// content : Function std::tolower

///////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cctype>
#include <cstddef>
#include <memory>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////

class Traits : public std::char_traits < char > 
{
public :

    static auto eq(char x, char y) { return std::tolower(x) == std::tolower(y); }

    static auto lt(char x, char y) { return std::tolower(x) <  std::tolower(y); }

//  -----------------------------------------------------------------------------------

    static auto compare(char const * string_1, char const * string_2, std::size_t size)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            if (!eq(string_1[i], string_2[i])) 
            {
                return lt(string_1[i], string_2[i]) ? -1 : +1;
            }
        }

        return 0;
    }

//  -----------------------------------------------------------------------------------

    static auto find(char const * string, std::size_t size, char x) -> char const *
    {
        for (auto i = 0uz; i < size; ++i)
        {
            if (eq(string[i], x)) 
            {
                return &string[i];
            }
        }

        return nullptr;
    }
};

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using string_t = std::basic_string < char, Traits, std::allocator < char > > ;

//  ------------------------------------------------------------------------------

    assert(string_t("aaaaa") == string_t("AAAAA"));

    assert(string_t("bbbbb") == string_t("BBBBB"));

    assert(string_t("aaaaa") != string_t("bbbbb"));

    assert(string_t("AAAAA") != string_t("BBBBB"));
}

///////////////////////////////////////////////////////////////////////////////////////