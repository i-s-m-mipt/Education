#include <iostream>

int main()
{
    std::cout << "Enter integer value: "; int x{};

    std::cout << (x > 0 ? x : 42) << std::endl;

//  ================================================================================================

    std::cout << "Enter integer value: ";

    if (std::cin >> x; 42 == x)
    {
        std::cout << "path 1" << std::endl;
    }
    else if (x > 0)
    {
        std::cout << "path 2" << std::endl;
    }
    else
    {
        if (x < 0)
        {
            std::cout << "path 3" << std::endl;
        }
        else
        { 
            std::cout << "path 4" << std::endl;
        }
    }

//  ================================================================================================

    std::cout << "Enter integer value: ";

    switch (std::cin >> x; x)
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
            std::cout << "path 2" << std::endl; break;
        }
        [[unlikely]] case 4:
        {
            std::cout << "path 3" << std::endl; break;
        }
        default:
        {
            std::cout << "path 4" << std::endl; break;
        }
    }

    return 0;
}