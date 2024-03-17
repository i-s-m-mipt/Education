#include <iostream>
#include <numeric>

template < typename T > class Ratio
{
public:

	Ratio(T num = T{}, T den = T(1)) : m_num(num), m_den(den)
	{
		if (m_den == T{}) // note: T{} used as zero value
		{
			std::cout << "invalid denominator" << std::endl;
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
		auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;
		m_den /= gcd;
	}

public:

	auto & operator+=(Ratio other) // note: same as in the non-template class
	{
		auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);

		m_den = lcm;

		reduce();

		return *this;
	}

	[[nodiscard]] friend inline const auto operator+(Ratio lhs, Ratio rhs) // good: friend inside class template
	{
		return (lhs += rhs);
	}

private:

	T m_num;
	T m_den;

}; // template < typename T > class Ratio

int main()
{
	[[maybe_unused]] auto result = 1 + Ratio < int > (1, 1); // note: free operator+ template doesn't work here

	return 0;
}