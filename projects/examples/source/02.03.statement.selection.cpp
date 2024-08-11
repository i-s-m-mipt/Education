#include <iostream>

int main()
{
    std::cout << "Enter integer: "; int x{}; std::cin >> x;

    std::cout << (x > 0 ? x : 42) << std::endl;

//  ================================================================================================

    std::cout << "Enter integer: "; int y{}; std::cin >> y;

    if (std::cout << "Path [0]" << std::endl; 42 == y)
    {
        std::cout << "Path [1]" << std::endl;
    }
    else if (y > 0)
    {
        std::cout << "Path [2]" << std::endl;
    }
    else
    {
        if (y < 0)
        {
            std::cout << "Path [3]" << std::endl;
        }
        else
        { 
            std::cout << "Path [4]" << std::endl;
        }
    }

//  ================================================================================================

    std::cout << "Enter integer: "; int z{}; std::cin >> z;

    switch (std::cout << "Path [0]" << std::endl; z)
    {
        [[likely]] case 0:
        [[likely]] case 1:
        [[likely]] case 2:
        {
            std::cout << "Path [1]" << std::endl;

            [[fallthrough]];
        }
        case 3:
        {
            std::cout << "Path [2]" << std::endl; break;
        }
        [[unlikely]] case 4:
        {
            std::cout << "Path [3]" << std::endl; break;
        }
        default:
        {
            std::cout << "Path [4]" << std::endl; break;
        }
    }

    return 0;
}