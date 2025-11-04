#include <cassert>
#include <cmath>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>
#include <compare>
#include <iostream>

class Rational
{
public:
    Rational(int num = 0, int den = 1) : m_num(num), m_den(den)
    {
        reduce();
    }

    explicit operator double() const
    { 
        return 1.0 * m_num / m_den;
    }

    auto & operator+=(Rational const & other)
    {
        auto lcm = std::lcm(m_den, other.m_den);
        m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
        m_den = lcm;
        reduce();
        return *this;
    }

    auto & operator-=(Rational const & other) 
    { 
        return *this += Rational(other.m_num * -1, other.m_den);
    }

    auto & operator*=(Rational const & other)
    {
        m_num *= other.m_num;
        m_den *= other.m_den;
        reduce();
        return *this;
    }
    
    auto & operator/=(Rational const & other) 
    { 
        return *this *= Rational(other.m_den, other.m_num);
    }
    
    auto const operator++(int) { auto x = *this; *this += 1; return x; }
    auto const operator--(int) { auto x = *this; *this -= 1; return x; }
    auto & operator++() { *this += 1; return *this; }
    auto & operator--() { *this -= 1; return *this; }

    friend auto operator+ (Rational lhs, Rational const & rhs) { return lhs += rhs; }
    friend auto operator- (Rational lhs, Rational const & rhs) { return lhs -= rhs; }
    friend auto operator* (Rational lhs, Rational const & rhs) { return lhs *= rhs; }
    friend auto operator/ (Rational lhs, Rational const & rhs) { return lhs /= rhs; }

    friend std::strong_ordering operator<=>(Rational const & lhs, Rational const & rhs)
    {
        // Чтобы сравнить дроби a/b и c/d, сравниваем a*d и b*c
        long long left_value = static_cast<long long>(lhs.m_num) * rhs.m_den;
        long long right_value = static_cast<long long>(rhs.m_num) * lhs.m_den;
        
        return left_value <=> right_value;
    }

    friend bool operator==(Rational const & lhs, Rational const & rhs) = default;

    friend auto & operator>>(std::istream & stream, Rational & rational)
    {
        return (stream >> rational.m_num).ignore() >> rational.m_den;
    }

    friend auto & operator<<(std::ostream & stream, Rational const & rational)
    {
        return stream << rational.m_num << '/' << rational.m_den;
    }

    void print() const {
        std::cout << m_num << "/" << m_den;
    }

private:
    void reduce()
    {
        if (m_den < 0)
        {
            m_num = -m_num;
            m_den = -m_den;
        }
        auto gcd = std::gcd(m_num, m_den);
        m_num /= gcd;
        m_den /= gcd;
    }

    int m_num = 0, m_den = 1;
};

auto equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;
}

int main()
{
    Rational x = 1, y(2, 1);

    std::vector < int > vector_2(5);
    std::vector < int > vector_3 = { 1, 2, 3, 4, 5 };

    assert(equal(static_cast < double > (x), 1));
    assert((x += y) == Rational(+3, 1));
    assert((x -= y) == Rational(+1, 1));
    assert((x *= y) == Rational(+2, 1));
    assert((x /= y) == Rational(+1, 1));
    assert((x ++  ) == Rational(+1, 1));
    assert((x --  ) == Rational(+2, 1));
    assert((  ++ y) == Rational(+3, 1));
    assert((  -- y) == Rational(+2, 1));

    [[maybe_unused]] auto z = 0;

    assert((x +  y) == Rational(+3, 1));
    assert((x -  y) == Rational(-1, 1));
    assert((x *  y) == Rational(+2, 1));
    assert((x /  y) == Rational(+1, 2));
    assert((x += 1) == Rational(+2, 1));
    assert((x +  1) == Rational(+3, 1));
    assert((1 +  y) == Rational(+3, 1));
    assert((1 +  1) == Rational(+2, 1));

    std::cout << "x = "; x.print(); std::cout << " = " << static_cast<double>(x) << std::endl;
    std::cout << "y = "; y.print(); std::cout << " = " << static_cast<double>(y) << std::endl;
    
    std::cout << "x < y: " << (x < y) << std::endl;
    std::cout << "x > y: " << (x > y) << std::endl;
    std::cout << "x == y: " << (x == y) << std::endl;

    assert((x <  y) == 0);
    assert((x >  y) == 0);
    assert((x <= y) == 1);
    assert((x >= y) == 1);
    assert((x == y) == 1);
    assert((x != y) == 0);

    std::stringstream stream_1("1/2");
    std::stringstream stream_2;
    stream_1 >> x;
    stream_2 << x;
    assert(stream_2.str() == "1/2");

    std::cout << "All tests passed!" << std::endl;
}