#include <iostream>
#include <numeric>

//  ================================================================================================

template < typename T > class Ratio // note: usually no problems with friend classes
{
public:

	Ratio(T num = T{}, T den = T(1)) : m_num(num), m_den(den)
	{
		if (m_den == T{}) // note: T{} used as zero value
		{
			std::cerr << "invalid denominator\n";
		}

		if (m_den <  T{}) // note: T{} used as zero value
		{
			m_num *= -1;
			m_den *= -1;
		}

		reduce();
	}

private:

	void reduce() // note: same as in the non-template class
	{
		const auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;
		m_den /= gcd;
	}

public:

	Ratio & operator+=(Ratio other) // note: same as in the non-template class
	{
		const auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);

		m_den = lcm;

		reduce();

		return *this;
	}

public:

	[[nodiscard]] friend inline Ratio operator+(Ratio lhs, Ratio rhs) // good: friend function inside class template
	{
		return (lhs += rhs);
	}

private:

	T m_num;
	T m_den;

}; // template < typename T > class Ratio

//  ================================================================================================

int main()
{
	[[maybe_unused]] const auto result = 1 + Ratio < int > (1, 1); // note: free operator+ template does not work here

	return 0;
}