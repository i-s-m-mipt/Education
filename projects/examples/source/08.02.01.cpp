#include <cassert>
#include <limits>

////////////////////////////////

auto pow(int x, int y)
{
    auto z = 1;

    if (x == 0) 
    {
        return y == 0 ? z : 0;
    }

    while (y > 0)
    {
        if (y & 1)
        {
            z *= x;
        }

        if (y /= 2; y == 0)
        {
            break;
        }

        x *= x;
    }

    return z;
}

////////////////////////////////

int main()
{
    assert(pow(2, 10) == 1'024);
}