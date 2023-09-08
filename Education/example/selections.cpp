#include <iostream>

int main()
{
    auto x = 0;

    std::cin >> x;

    if (auto y = x * 4 + 10; 42 == y)
    {
        std::cout << "path 1\n";
    }
    else if (y > 0)
    {
        std::cout << "path 2\n";
    }
    else
    {
        if (x < 0)
        {
            std::cout << "path 3\n";
        }
        else
        { 
            std::cout << "path 4\n";
        }
    }

    std::cout << (x > 0 ? x : 42) << '\n';

    switch (auto y = x / 4 - 1; y)
    {
    [[likely]] case 0:
    [[likely]] case 1:
    [[likely]] case 2:
    {
        std::cout << "path 1" << std::endl;
        [[fallthrough]];
    }
    case 3:
    {
        std::cout << "path 2" << std::endl;
        break;
    }
    [[unlikely]] case 4:
    {
        std::cout << "path 3" << std::endl;
        break;
    }
    default:
    {
        std::cout << "path 4" << std::endl;
        break;
    }
    }

    return 0;
}
