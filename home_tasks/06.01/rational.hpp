#pragma once

#include <compare>
#include <iosfwd>
#include <cstdint>
#include <stdexcept>

template <typename T> class addable
{
public:
    friend auto operator+ (T lhs, T const & rhs) { return lhs += rhs; }

protected:
    addable() = default;
    ~addable() = default;
};

template <typename T> class subtractable
{
public:
    friend auto operator- (T lhs, T const & rhs) { return lhs -= rhs; }

protected:
    subtractable() = default;
    ~subtractable() = default;
};

template <typename T> class multipliable
{
public:
    friend auto operator* (T lhs, T const & rhs) { return lhs *= rhs; }

protected:
    multipliable() = default;
    ~multipliable() = default;
};

template <typename T> class dividable
{
public:
    friend auto operator/ (T lhs, T const & rhs) { return lhs /= rhs; }

protected:
    dividable() = default;
    ~dividable() = default;
};

template <typename T> class incrementable
{
public:
    auto & operator++() { 
        T& self = static_cast<T&>(*this);
        self += T(1);
        return self;
    }

    T operator++(int) { 
        T temp = static_cast<T&>(*this);
        ++static_cast<T&>(*this);
        return temp;
     }

protected:
    incrementable() = default;
    ~incrementable() = default;
};

template <typename T> class decrementable
{
public:
    auto & operator--() { 
        T& self = static_cast<T&>(*this);
        self -= T(1);
        return self;
    }

    T operator--(int) { 
        T temp = static_cast<T&>(*this);
        --static_cast<T&>(*this);
        return temp;
     }

protected:
    decrementable() = default;
    ~decrementable() = default;
};

class Rational :
    public addable <Rational>,
    public subtractable <Rational>,
    public multipliable <Rational>,
    public dividable <Rational>,
    public incrementable <Rational>,
    public decrementable <Rational>
{
private:
    int m_num = 0;
    int m_den = 1;
    
    void reduce();

public:
    Rational(int num = 0, int den = 1) : m_num(num), m_den(den)
    {
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }

    Rational(const Rational&) = default;
    
    Rational& operator=(const Rational&) = default;

    explicit operator double() const
    { 
        return static_cast<double>(m_num) / m_den;
    }

    int numerator() const { return m_num; }
    int denominator() const { return m_den; }

    Rational& operator+=(Rational const& other);
    Rational& operator-=(Rational const& other);
    Rational& operator*=(Rational const& other);
    Rational& operator/=(Rational const& other);
    
    Rational& operator+=(int other);
    Rational& operator-=(int other);
    Rational& operator*=(int other);
    Rational& operator/=(int other);

    friend bool operator==(Rational const& lhs, Rational const& rhs);
    friend std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs);

    friend std::istream& operator>>(std::istream& stream, Rational& rational);
    friend std::ostream& operator<<(std::ostream& stream, Rational const& rational);

    void print() const;
};

bool equal(double x, double y, double epsilon = 1e-6);

Rational operator+(Rational lhs, int rhs);
Rational operator+(int lhs, Rational rhs);
Rational operator-(Rational lhs, int rhs);
Rational operator-(int lhs, Rational rhs);
Rational operator*(Rational lhs, int rhs);
Rational operator*(int lhs, Rational rhs);
Rational operator/(Rational lhs, int rhs);
Rational operator/(int lhs, Rational rhs);