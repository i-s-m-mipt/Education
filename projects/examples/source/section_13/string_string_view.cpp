#include <cassert>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>

struct ignorecase_traits : public std::char_traits < char > 
{
    static bool eq(char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }
    static bool lt(char c1, char c2) { return std::toupper(c1) <  std::toupper(c2); }

    static int compare(const char * s1, const char * s2, std::size_t n) 
    {
        for (std::size_t i = 0; i < n; ++i) 
        {
            if (!eq(s1[i], s2[i])) return lt(s1[i], s2[i]) ? -1 : +1;
        }

        return 0;
    }
    
    static const char * find(const char * s, std::size_t n, char c) 
    {
        for (std::size_t i = 0; i < n; ++i) 
        {
            if (eq(s[i], c)) return &(s[i]);
        }

        return nullptr;
    }

}; // struct ignorecase_traits : public std::char_traits < char > 

using icstring_t = std::basic_string < char, ignorecase_traits > ;

inline std::ostream & operator<<(std::ostream & stream, const icstring_t & icstring)
{
    return (stream << std::string(icstring.data(), std::size(icstring)));
}

int main()
{
    std::cout << "Enter string 1: "; std::string string_1; std::cin >> string_1;
    std::cout << "Enter string 2: "; std::string string_2; 
    
    std::getline(std::cin >> std::ws, string_2); // good: skip space characters

    std::cout << std::quoted(string_1) << ' ' << 
                 std::quoted(string_2) << std::endl; // note: see arguments

    using namespace std::literals;

    const auto string_3 = "Hello, world!"s; // good: standard string literal for auto

    if (const auto index = string_3.find(','); index != std::string::npos)
    {
        assert(string_3.substr(0, index) == "Hello"s);
    }

    assert(string_3.starts_with("Hello"s) && string_3.ends_with('!'));

    auto string_4 = "43"s; string_4.erase(1); string_4.append("2"s);

    assert(std::stoi(string_4) == 42 && string_4 == std::to_string(42));

    [[maybe_unused]] constexpr char char_array[]{ 'H', 'e', 'l', 'l', 'o'       };

    [[maybe_unused]] constexpr char c_string_1[]{ 'H', 'e', 'l', 'l', 'o', '\0' };
    
    [[maybe_unused]] constexpr char c_string_2[] = "Hello";
    [[maybe_unused]] constexpr auto c_string_3   = "Hello"; // note: auto -> const char *

    assert(std::strcmp(string_3.c_str(), c_string_3) > 0); // note: C-library compatibility

    assert(icstring_t("HELLO") == icstring_t("hello"));    

    return 0;
}