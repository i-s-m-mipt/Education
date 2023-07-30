#include <iostream>

int main()
{
    auto x = 0;
    auto y = 1;

    if (x > y)
    {
        std::cout << "path 1\n";
    }
    else if (x < y)
    {
        std::cout << "path 2\n";
    }
    else
    {
        std::cout << "path 3\n";
    }

    if (x < y)
    {
        if (x < 1)
        { /*...*/ }
        else
        { /*...*/ }
    }

    if (auto value = x + y; value < 42)
    { /*...*/ }

    auto z = (x < y ? x : 0);

    system("pause");

    return 0;
}
