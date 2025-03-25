#include <cassert>
#include <cmath>
#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////

class Rational
{
public :

	/* explicit */ Rational(int num = 0, int den = 1) : m_num(num), m_den(den)
	{
		reduce();
	}

//  -------------------------------------------------------------------------------------------

	explicit operator double() const
	{ 
		return 1.0 * m_num / m_den;
	}

//  -------------------------------------------------------------------------------------------

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

	auto & operator*=(const Rational & other)
	{
		m_num *= other.m_num;

		m_den *= other.m_den;

		reduce();

		return *this;
	}
	
	auto & operator/=(const Rational & other) 
	{ 
		return *this *= Rational(other.m_den, other.m_num);
	}

//  -------------------------------------------------------------------------------------------

	const auto   operator++(int) { auto copy = *this; *this += 1; return  copy; } 

	      auto & operator++(   ) {                    *this += 1; return *this; }

	const auto   operator--(int) { auto copy = *this; *this -= 1; return  copy; } 

	      auto & operator--(   ) {                    *this -= 1; return *this; }

//  -------------------------------------------------------------------------------------------

	friend auto operator+ (const Rational & lhs, const Rational & rhs) 
	{ 
		return Rational(lhs) += rhs;
	}

	friend auto operator- (const Rational & lhs, const Rational & rhs) 
	{ 
		return Rational(lhs) -= rhs;
	}

	friend auto operator* (const Rational & lhs, const Rational & rhs) 
	{ 
		return Rational(lhs) *= rhs;
	}

	friend auto operator/ (const Rational & lhs, const Rational & rhs) 
	{ 
		return Rational(lhs) /= rhs;
	}

//  -------------------------------------------------------------------------------------------

	friend auto operator< (const Rational & lhs, const Rational & rhs)
	{
		return static_cast < double > (lhs) < static_cast < double > (rhs);
	}

	friend auto operator> (const Rational & lhs, const Rational & rhs) { return  (rhs < lhs); }
	
	friend auto operator<=(const Rational & lhs, const Rational & rhs) { return !(lhs > rhs); }

	friend auto operator>=(const Rational & lhs, const Rational & rhs) { return !(lhs < rhs); }

	friend auto operator==(const Rational & lhs, const Rational & rhs)
	{
		return !(lhs < rhs) && !(rhs < lhs);
	}

//  -------------------------------------------------------------------------------------------

	friend auto & operator>>(std::istream & stream, Rational & rational)
	{
		stream >> rational.m_num; 
		
		stream.get();

		stream >> rational.m_den;
		
		return stream;
	}

	friend auto & operator<<(std::ostream & stream, const Rational & rational)
	{
		return stream << rational.m_num << '/' << rational.m_den;
	}

private :

	void reduce()
	{
		auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;

		m_den /= gcd;
	}

//  -------------------------------------------------------------------------------------------

	int m_num = 0, m_den = 1;
};

///////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rational x = 1, y(2, 1);

//  -------------------------------------------------

//	std::vector < int > vector = 1; // error

//  -------------------------------------------------

	assert(equal(static_cast < double > (x), 1));

//  -------------------------------------------------

//	assert(x.operator+=(y) == Rational(3, 1)); // bad

//  -------------------------------------------------

	assert((x += y) == Rational(+3, 1));

	assert((x -= y) == Rational(+1, 1));

	assert((x *= y) == Rational(+2, 1));

	assert((x /= y) == Rational(+1, 1));

//  -------------------------------------------------

	assert((x ++  ) == Rational(+1, 1));

	assert((  ++ y) == Rational(+3, 1));

	assert((x --  ) == Rational(+2, 1));

	assert((  -- y) == Rational(+2, 1));

//  -------------------------------------------------

//	x++++; // error

//  -------------------------------------------------

//	assert(operator+(x, y) == Rational(3, 1)); // bad

//  -------------------------------------------------

	assert((x +  y) == Rational(+3, 1));

	assert((x -  y) == Rational(-1, 1));

	assert((x *  y) == Rational(+2, 1));

	assert((x /  y) == Rational(+1, 2));

//  -------------------------------------------------

	assert((x += 1) == Rational(+2, 1));

	assert((x +  1) == Rational(+3, 1));

	assert((1 +  y) == Rational(+3, 1));

	assert((1 +  1) == Rational(+2, 1));

//  -------------------------------------------------

	assert((x <  y) == 0);
	
	assert((x >  y) == 0);

	assert((x <= y) == 1);

	assert((x >= y) == 1);

	assert((x == y) == 1);

	assert((x != y) == 0);

//  -------------------------------------------------

	std::stringstream stream_1("1/2");

	std::stringstream stream_2;
	
//  -------------------------------------------------

	stream_1 >> x;

	stream_2 << x;

//  -------------------------------------------------

	assert(stream_2.str() == stream_1.str());
}