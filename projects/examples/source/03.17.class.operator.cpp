#include <cassert>
#include <cmath>
#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>
#include <vector>

#include <boost/rational.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////

class Rational
{
public:

	/* explicit */ Rational(int num = 0, int den = 1) : m_num(num), m_den(den)
	{
		if (m_den == 0) { std::cerr << "Rational::Rational : invalid denominator\n"; }

		if (m_den <  0)
		{
			m_num *= -1;
			
			m_den *= -1;
		}

		reduce();
	}

//  ------------------------------------------------------------------------------------------

	explicit operator double() const
	{ 
		return 1.0 * m_num / m_den;
	}

//  ------------------------------------------------------------------------------------------

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

//  ------------------------------------------------------------------------------------------

	const auto   operator++(int) { auto copy(*this); *this += 1; return  copy; } 

	      auto & operator++(   ) {                   *this += 1; return *this; }

	const auto   operator--(int) { auto copy(*this); *this -= 1; return  copy; } 

	      auto & operator--(   ) {                   *this -= 1; return *this; }

//  ------------------------------------------------------------------------------------------

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

//  ------------------------------------------------------------------------------------------

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

//  ------------------------------------------------------------------------------------------

	friend auto & operator>>(std::istream & stream, Rational & rational)
	{
		auto num = 0; char x = 0; auto den = 0; stream >> num >> x >> den;

		if (x != '/') 
		{
			std::cerr << "operator>> : invalid rational\n";
		}

		rational = Rational(num, den);
		
		return stream;
	}

	friend auto & operator<<(std::ostream & stream, const Rational & rational)
	{
		return stream << rational.m_num << '/' << rational.m_den;
	}

private:

	void reduce()
	{
		auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;

		m_den /= gcd;
	}

//  ------------------------------------------------------------------------------------------

	int m_num = 0, m_den = 1;
};

//////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		[[maybe_unused]] Rational x1, x2(2), x3 = 3, x4(4, 1);

//		std::vector < int > vector = 1; // error
	}

//  -----------------------------------------------------------------

	{
		Rational x = 1, y = 2;

		assert(equal(static_cast < double > (x), 1.0));

//		assert(x.operator+=(y) == Rational(3, 1)); // bad

		assert((x += y) == Rational(3, 1));
		assert((x += 1) == Rational(4, 1));
//		assert((1 += y) == Rational(3, 1)); // error
//		assert((1 += 1) == Rational(2, 1)); // error

		assert((x -= y) == Rational(2, 1));
		assert((x *= y) == Rational(4, 1));
		assert((x /= y) == Rational(2, 1));

		assert((x ++  ) == Rational(2, 1));
		assert((  ++ y) == Rational(3, 1));
		assert((x --  ) == Rational(3, 1));
		assert((  -- y) == Rational(2, 1));

//		x++++; // error

//		assert(operator+(x, y) == Rational(4, 1)); // bad

		assert((x +  y) == Rational(4, 1));
		assert((x +  1) == Rational(3, 1));
		assert((1 +  y) == Rational(3, 1));
		assert((1 +  1) == Rational(2, 1));

		assert((x -  y) == Rational(0, 1));
		assert((x *  y) == Rational(4, 1));
		assert((x /  y) == Rational(1, 1));

		assert((x <  y) == 0);
		assert((x >  y) == 0);
		assert((x <= y) == 1);
		assert((x >= y) == 1);
		assert((x == y) == 1);
		assert((x != y) == 0);
	}

//  -----------------------------------------------------------------

	{
		std::cout << "main : enter Rational : "; Rational x; std::cin >> x; 
	
		std::cout << "main : x = " << x << '\n';
	}

//  -----------------------------------------------------------------

	{
		boost::rational < int > x = 1, y = 2;

		assert(equal(boost::rational_cast < double > (x), 1.0));

		assert((x += y) == boost::rational < int > (3, 1));
		assert((x += 1) == boost::rational < int > (4, 1));
		assert((x -= y) == boost::rational < int > (2, 1));
		assert((x *= y) == boost::rational < int > (4, 1));
		assert((x /= y) == boost::rational < int > (2, 1));

		assert((x ++  ) == boost::rational < int > (2, 1));
		assert((  ++ y) == boost::rational < int > (3, 1));
		assert((x --  ) == boost::rational < int > (3, 1));
		assert((  -- y) == boost::rational < int > (2, 1));

		assert((x +  y) == boost::rational < int > (4, 1));
		assert((x +  1) == boost::rational < int > (3, 1));
		assert((1 +  y) == boost::rational < int > (3, 1));
		assert((1 +  1) == boost::rational < int > (2, 1));

		assert((x -  y) == boost::rational < int > (0, 1));
		assert((x *  y) == boost::rational < int > (4, 1));
		assert((x /  y) == boost::rational < int > (1, 1));

		assert((x <  y) == 0);
		assert((x >  y) == 0);
		assert((x <= y) == 1);
		assert((x >= y) == 1);
		assert((x == y) == 1);
		assert((x != y) == 0);
	}

//  -----------------------------------------------------------------

	{
		std::cout << "main : enter boost::rational < int > : ";
		
		boost::rational < int > x; std::cin >> x;
	
		std::cout << "main : x = " << x << '\n';
	}
}