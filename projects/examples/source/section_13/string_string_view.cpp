#include <iomanip>
#include <iostream>
#include <string>

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
        std::cout << string_3.substr(0, index) << std::endl;
    }

    /*
    const char char_array[]{ 'H', 'e', 'l', 'l', 'o' };

    const char   string_1[]{ 'H', 'e', 'l', 'l', 'o', '\0' };
    const char   string_2[] = "Hello";
    const char* string_3 = "Hello";

    char string_4[] = "Hello";

    string_4[4] = '!';

    std::cout << sizeof(string_1) << std::endl;
    std::cout << std::size(string_1) << std::endl;
    std::cout << std::strlen(string_1) << std::endl;

    std::cout << string_1;

    auto text = f();

    std::cout << text << std::endl;

    std::string string_5 = "Hello";

    using namespace std::string_literals;

    auto string_6 = "Hello"s;
    auto string_7 = u8"Hello"s;
    auto string_8 = u"Hello"s;
    auto string_9 = U"Hello"s;
    */

    return 0;
}