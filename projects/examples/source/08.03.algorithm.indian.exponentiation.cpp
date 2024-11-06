#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

//  ================================================================================================

[[nodiscard]] auto pow(unsigned long long base, unsigned long long exp)
{
    auto result = 1ull;

    if (base == 0) 
    {
        return exp == 0 ? result : 0;
    }

    while (exp > 0)
    {
        if (exp & 1)
        {
            if (result > std::numeric_limits < unsigned long long > ::max() / base)
            {
                throw std::runtime_error("arithmetic overflow");
            }

            result *= base;
        }

        if (exp /= 2; exp == 0) 
        {
            break;
        }

        if (base > std::numeric_limits < unsigned long long > ::max() / base)
        {
            throw std::runtime_error("arithmetic overflow");
        }

        base *= base;
    }

    return result;
}

//  ================================================================================================

int main()
{
    assert(pow(2, 32) == 4'294'967'296);

	try
    {
        std::ignore = pow(2, 64);
    }
    catch (const std::exception & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }
}