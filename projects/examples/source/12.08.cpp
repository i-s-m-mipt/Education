///////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cctype>
#include <cstddef>
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
    assert
    (
        (std::basic_string < char, Traits > ("aaaaa")) == 
        
        (std::basic_string < char, Traits > ("AAAAA"))
    );
}

///////////////////////////////////////////////////////////////////////////////////////