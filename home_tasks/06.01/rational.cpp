#include "rational.hpp"
#include <iostream>
#include <numeric>
#include <cmath>
#include <stdexcept>

bool equal(double x, double y, double epsilon)
{
    return std::abs(x - y) < epsilon;
}

void Rational::reduce()
{
    if (m_den < 0)
    {
        m_num = -m_num;
        m_den = -m_den;
    }
    auto gcd = std::gcd(m_num, m_den);
    if (gcd > 1) {
        m_num /= gcd;
        m_den /= gcd;
    }
}

Rational& Rational::operator+=(Rational const& other)
{
    auto lcm = std::lcm(m_den, other.m_den);
    m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
    m_den = lcm;
    reduce();
    return *this;
}

Rational& Rational::operator-=(Rational const& other) 
{ 
    return *this += Rational(-other.m_num, other.m_den);
}

Rational& Rational::operator*=(Rational const& other)
{
    m_num *= other.m_num;
    m_den *= other.m_den;
    reduce();
    return *this;
}

Rational& Rational::operator/=(Rational const& other) 
{ 
    if (other.m_num == 0) {
        throw std::runtime_error("Division by zero");
    }
    return *this *= Rational(other.m_den, other.m_num);
}

Rational& Rational::operator+=(int other)
{
    return *this += Rational(other);
}

Rational& Rational::operator-=(int other)
{
    return *this -= Rational(other);
}

Rational& Rational::operator*=(int other)
{
    return *this *= Rational(other);
}

Rational& Rational::operator/=(int other)
{
    return *this /= Rational(other);
}

bool operator==(Rational const& lhs, Rational const& rhs)
{
    return !(lhs < rhs) && !(rhs < lhs);
}

std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs)
{
    long long left_value = static_cast<long long>(lhs.m_num) * rhs.m_den;
    long long right_value = static_cast<long long>(rhs.m_num) * lhs.m_den;
    return left_value <=> right_value;
}

std::istream& operator>>(std::istream& stream, Rational& rational)
{
    int num, den;
    char slash;
    
    // Пытаемся прочитать в формате "число/число"
    if (stream >> num) {
        if (stream.get(slash) && slash == '/' && stream >> den) {
            rational = Rational(num, den);
        } else {
            // Если нет '/', то это целое число
            stream.clear();
            rational = Rational(num);
        }
    } else {
        stream.setstate(std::ios::failbit);
    }
    
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Rational const& rational)
{
    if (rational.denominator() == 1) {
        return stream << rational.numerator();
    }
    return stream << rational.numerator() << '/' << rational.denominator();
}

void Rational::print() const {
    std::cout << m_num << "/" << m_den;
}

Rational operator+(Rational lhs, int rhs)
{
    return lhs += rhs;
}

Rational operator+(int lhs, Rational rhs)
{
    return Rational(lhs) += rhs;
}

Rational operator-(Rational lhs, int rhs)
{
    return lhs -= rhs;
}

Rational operator-(int lhs, Rational rhs)
{
    return Rational(lhs) -= rhs;
}

Rational operator*(Rational lhs, int rhs)
{
    return lhs *= rhs;
}

Rational operator*(int lhs, Rational rhs)
{
    return Rational(lhs) *= rhs;
}

Rational operator/(Rational lhs, int rhs)
{
    return lhs /= rhs;
}

Rational operator/(int lhs, Rational rhs)
{
    return Rational(lhs) /= rhs;
}