#include <cassert>
#include <iostream>
#include <numeric>

//////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Rational
{
public:

	Rational(T num = T(0), T den = T(1)) : m_num(num), m_den(den)
	{
		if (m_den == T(0)) { std::cerr << "Rational::Rational : invalid denominator\n"; }

		if (m_den <  T(0))
		{
			m_num *= -1;

			m_den *= -1;
		}

		reduce();
	}

//  -------------------------------------------------------------------------------------

	explicit operator double() const 
	{ 
		return 1.0 * m_num / m_den;
	}

//  -------------------------------------------------------------------------------------

	auto & operator+=(const Rational & other)
	{
		auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
		
		m_den = lcm;

		reduce();

		return *this;
	}

	auto & operator-=(const Rational & other) 
	{ 
		return *this += other.m_num * -1;
	}

//  -------------------------------------------------------------------------------------

	friend auto operator+ (const Rational & lhs, const Rational & rhs) 
	{ 
		return Rational(lhs) += rhs;
	}

//  -------------------------------------------------------------------------------------

	friend auto operator< (const Rational & lhs, const Rational & rhs)
	{
		return static_cast < double > (lhs) < static_cast < double > (rhs);
	}

	friend auto operator==(const Rational & lhs, const Rational & rhs)
	{
		return !(lhs < rhs) && !(rhs < lhs);
	}

private:

	void reduce()
	{
		auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;

		m_den /= gcd;
	}

//  -------------------------------------------------------------------------------------

	T m_num = T(0), m_den = T(1);
};

//////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto operator-(const Rational < T > & lhs, const Rational < T > & rhs)
{ 
	return Rational < T > (lhs) -= rhs;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rational < int > x = 1;

//  ------------------------------------------------------------

	assert(x + 1 == Rational < int > (2, 1));

//	assert(x - 1 == Rational < int > (0, 1)); // error

//  ------------------------------------------------------------

	assert(operator- < int > (x, 1) == Rational < int > (0, 1));
}