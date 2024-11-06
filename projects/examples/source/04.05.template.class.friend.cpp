#include <cassert>
#include <iostream>
#include <numeric>
#include <utility>

//  ================================================================================================

template < typename T > class Ratio
{
public:

	Ratio(T num = T(0), T den = T(1)) : m_num(num), m_den(den)
	{
		if (m_den == T(0)) 
		{ 
			std::cerr << "Ratio::Ratio : invalid denominator\n"; 
		}

		if (m_den < T(0))
		{
			m_num *= -1;
			m_den *= -1;
		}

		reduce();
	}

	[[nodiscard]] explicit operator double() const 
	{ 
		return 1.0 * m_num / m_den; 
	}

private:

	void reduce()
	{
		auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;
		m_den /= gcd;
	}

public:

	auto & operator+=(Ratio other)
	{
		auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den); m_den = lcm;

		reduce();

		return *this;
	}

	auto & operator-=(Ratio other) 
	{ 
		return *this += other.m_num *= -1; 
	}

//  ------------------------------------------------------------------------------------------------

	[[nodiscard]] friend auto operator+(Ratio lhs, Ratio rhs) 
	{ 
		return lhs += rhs; 
	}

//  ------------------------------------------------------------------------------------------------

	[[nodiscard]] friend auto operator< (Ratio lhs, Ratio rhs)
	{
		return static_cast < double > (lhs) < static_cast < double > (rhs);
	}

	[[nodiscard]] friend auto operator==(Ratio lhs, Ratio rhs)
	{
		return !(lhs < rhs) && !(rhs < lhs);
	}

private:

	T m_num = T(0);
	T m_den = T(1);
};

//  ================================================================================================

template < typename U > [[nodiscard]] auto operator-(Ratio < U > lhs, Ratio < U > rhs)
{ 
	return lhs -= rhs;
}

//  ================================================================================================

int main()
{
	Ratio < int > ratio(1, 1);

//  ------------------------------------------

	assert(1 + ratio == Ratio < int > (2, 1));
//	assert(1 - ratio == Ratio < int > (0, 1)); // error

//  -------------------------------------------------------------

	assert(operator- < int > (1, ratio) == Ratio < int > (0, 1));
}