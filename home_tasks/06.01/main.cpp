#include "rational.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>

int main()
{
    Rational x(1);
    Rational y(2, 1);

    std::vector<int> vector_2(5);
    std::vector<int> vector_3 = { 1, 2, 3, 4, 5 };

    assert(equal(static_cast<double>(x), 1.0));
    assert((x += y) == Rational(+3, 1));
    assert((x -= y) == Rational(+1, 1));
    assert((x *= y) == Rational(+2, 1));
    assert((x /= y) == Rational(+1, 1));
    
    Rational temp_x = x;
    assert((x++) == temp_x);
    assert(x == Rational(+2, 1));
    
    temp_x = x;
    assert((x--) == temp_x);
    assert(x == Rational(+1, 1));
    
    Rational temp_y = y;
    assert((++y) == Rational(temp_y.numerator() + 1, 1));
    assert((--y) == Rational(+2, 1));

    [[maybe_unused]] auto z = 0;

    assert((x + y) == Rational(+3, 1));
    assert((x - y) == Rational(-1, 1));
    assert((x * y) == Rational(+2, 1));
    assert((x / y) == Rational(+1, 2));
    
    x = Rational(1, 1);
    assert((x += 1) == Rational(+2, 1));
    assert((x + 1) == Rational(+3, 1));
    assert((1 + y) == Rational(+3, 1));

    std::cout << "x = "; x.print(); std::cout << " = " << static_cast<double>(x) << std::endl;
    std::cout << "y = "; y.print(); std::cout << " = " << static_cast<double>(y) << std::endl;
    
    std::cout << "x < y: " << (x < y) << std::endl;
    std::cout << "x > y: " << (x > y) << std::endl;
    std::cout << "x == y: " << (x == y) << std::endl;

    assert((x < y) == false);
    assert((x > y) == false);
    assert((x <= y) == true);
    assert((x >= y) == true);
    assert((x == y) == true);
    assert((x != y) == false);

    std::stringstream stream_1("1/2");
    std::stringstream stream_2;
    stream_1 >> x;
    stream_2 << x;
    assert(stream_2.str() == "1/2");

    {
        Rational a(1, 3);
        Rational b(1, 6);
        
        std::cout << "\nДополнительные тесты:" << std::endl;
        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        std::cout << "a + b = " << (a + b) << std::endl;
        std::cout << "a - b = " << (a - b) << std::endl;
        
        assert((a + b) == Rational(1, 2));
        assert((a - b) == Rational(1, 6));
    }

    std::cout << "\nAll tests passed!" << std::endl;
    
    return 0;
}