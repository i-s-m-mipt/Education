#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

unsigned long long pow(unsigned long long base, unsigned long long exp)
{
    if (base == 0) return (exp == 0) ? 1 : 0;

    auto result = 1ull;

    while (exp > 0)
    {
        if (exp & 1) // note: checks if exp is odd
        {
            if (result > std::numeric_limits < unsigned long long > ::max() / base)
            {
                throw std::overflow_error("overflow: " + std::to_string(result) + '*' + std::to_string(base));
            }

            result *= base;
        }

        exp /= 2;

        if (exp == 0) break;

        if (base > std::numeric_limits < unsigned long long > ::max() / base)
        {
            throw std::overflow_error("overflow: " + std::to_string(result) + '*' + std::to_string(base));
        }

        base *= base;
    }

    return result;
}

int main()
{
	try
    {
        assert(pow(2,  0) == 1);
        assert(pow(2,  1) == 2);
        assert(pow(2,  2) == 4);
        assert(pow(2,  4) == 16);
        assert(pow(2,  8) == 256);
        assert(pow(2, 16) == 65536);
        assert(pow(2, 32) == 4294967296);

        std::cout << "all tests passed" << std::endl;

        [[maybe_unused]] auto result = pow(2, 64); // note: throws an exception
    }
    catch(const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }

	return 0;
}