//////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <numeric>

//////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Rational
{
public :

	Rational(T num = 0, T den = 1) : m_num(num), m_den(den)
	{
		reduce();
	}

//  ----------------------------------------------------------------------

	explicit operator double() const 
	{ 
		return 1.0 * m_num / m_den;
	}

//  ----------------------------------------------------------------------

	auto & operator+=(Rational const & other)
	{
		auto lcm = std::lcm(m_den, other.m_den);

	//  ------------------------------------------------------------------

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
		
		m_den = lcm;

	//  ------------------------------------------------------------------

		reduce();

		return *this;
	}

//  ----------------------------------------------------------------------

	auto & operator-=(Rational const & other) 
	{ 
		return *this += other.m_num * -1;
	}

//  ----------------------------------------------------------------------

	friend auto operator+ (Rational lhs, Rational const & rhs) 
	{ 
		return lhs += rhs;
	}

//  ----------------------------------------------------------------------

	friend auto operator< (Rational const & lhs, Rational const & rhs)
	{
		return lhs.m_num * rhs.m_den < rhs.m_num * lhs.m_den;
	}

//  ----------------------------------------------------------------------

	friend auto operator==(Rational const & lhs, Rational const & rhs)
	{
		return !(lhs < rhs) && !(rhs < lhs);
	}

private :

	void reduce()
	{
		auto gcd = std::gcd(m_num, m_den);

	//  ----------------------------------

		m_num /= gcd;

		m_den /= gcd;
	}

//  -----------------------------------------------------------------------

	T m_num = 0, m_den = 1;
};

//////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto operator-(Rational < T > lhs, Rational < T > const & rhs)
{ 
	return lhs -= rhs;
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rational < int > x = 1;

//  ------------------------------------------------------------

	assert(x + 1 == Rational < int > (2, 1));

//	assert(x - 1 == Rational < int > (0, 1)); // error

//  ------------------------------------------------------------

	assert(operator- < int > (x, 1) == Rational < int > (0, 1));
}

//////////////////////////////////////////////////////////////////////////////////////