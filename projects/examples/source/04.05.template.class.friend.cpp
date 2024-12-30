#include <cassert>
#include <iostream>
#include <numeric>

////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Ratio
{
public:

	Ratio(T num = T(0), T den = T(1)) : m_num(num), m_den(den)
	{
		if (m_den == T(0)) { std::cerr << "Ratio::Ratio : invalid denominator\n"; }

		if (m_den <  T(0))
		{
			m_num *= -1;
			m_den *= -1;
		}

		reduce();
	}

//  -----------------------------------------------------------------------------------

	explicit operator double() const 
	{ 
		return 1.0 * m_num / m_den; 
	}

//  -----------------------------------------------------------------------------------

	auto & operator+=(const Ratio & other)
	{
		auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den); 
		
		m_den = lcm;

		reduce();

		return *this;
	}

	auto & operator-=(const Ratio & other) 
	{ 
		return *this += other.m_num * -1; 
	}

//  -----------------------------------------------------------------------------------

	friend auto operator+ (const Ratio & lhs, const Ratio & rhs) 
	{ 
		return Ratio(lhs) += rhs; 
	}

//  -----------------------------------------------------------------------------------

	friend auto operator< (const Ratio & lhs, const Ratio & rhs)
	{
		return static_cast < double > (lhs) < static_cast < double > (rhs);
	}

	friend auto operator==(const Ratio & lhs, const Ratio & rhs)
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

//  -----------------------------------------------------------------------------------

	T m_num = T(0);
	T m_den = T(1);
};

////////////////////////////////////////////////////////////////////////////////////////

template < typename U > auto operator-(const Ratio < U > & lhs, const Ratio < U > & rhs)
{ 
	return Ratio < U > (lhs) -= rhs;
}

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Ratio < int > ratio(1, 1);

//  -------------------------------------------------------------

	assert(1 + ratio == Ratio < int > (2, 1));
//	assert(1 - ratio == Ratio < int > (0, 1)); // error

//  -------------------------------------------------------------

	assert(operator- < int > (1, ratio) == Ratio < int > (0, 1));
}