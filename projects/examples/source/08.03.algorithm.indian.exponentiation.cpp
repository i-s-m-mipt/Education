#include <cassert>
#include <exception>
#include <limits>
#include <stdexcept>

//  ================================================================================================

auto pow(unsigned long long x, unsigned long long y)
{
    auto z = 1ull;

    if (x == 0) 
    {
        return y == 0 ? z : 0;
    }

    while (y > 0)
    {
        if (y & 1)
        {
            if (z > std::numeric_limits < unsigned long long > ::max() / x)
            {
                throw std::runtime_error("arithmetic overflow");
            }

            z *= x;
        }

        if (y /= 2; y == 0) 
        {
            break;
        }

        if (x > std::numeric_limits < unsigned long long > ::max() / x)
        {
            throw std::runtime_error("arithmetic overflow");
        }

        x *= x;
    }

    return z;
}

//  ================================================================================================

int main()
{
    assert(pow(2, 32) == 4'294'967'296);
}