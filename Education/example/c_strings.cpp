#include <cstring>
#include <iostream>

const char* f()
{
    return "Hello";
}

int main()
{
    const char char_array[]{ 'H', 'e', 'l', 'l', 'o' };

    const char  string_1[]{ 'H', 'e', 'l', 'l', 'o', '\0' };
    const char  string_2[] = "Hello";
    const char* string_3   = "Hello";

    std::cout << sizeof(string_1)      << std::endl;
    std::cout << std::size(string_1)   << std::endl;
    std::cout << std::strlen(string_1) << std::endl;

    std::cout << string_1;

    auto text = f();

    std::cout << text << std::endl;

    system("pause");

    return 0;
}