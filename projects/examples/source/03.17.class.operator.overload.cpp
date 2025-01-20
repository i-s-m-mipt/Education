#include <cassert>
#include <cmath>
#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>
#include <vector>

#include <boost/rational.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////

class Ratio
{
public:

	/* explicit */ Ratio(int num = 0, int den = 1) : m_num(num), m_den(den)
	{
		if (m_den == 0) { std::cerr << "Ratio::Ratio : invalid denominator\n"; }

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

	auto & operator*=(const Ratio & other)
	{
		m_num *= other.m_num;

		m_den *= other.m_den;

		reduce();

		return *this;
	}
	
	auto & operator/=(const Ratio & other) 
	{ 
		return *this *= Ratio(other.m_den, other.m_num); 
	}

//  ------------------------------------------------------------------------------------------

	const auto   operator++(int) { auto copy(*this); *this += 1; return  copy; } 

	      auto & operator++(   ) {                   *this += 1; return *this; }

	const auto   operator--(int) { auto copy(*this); *this -= 1; return  copy; } 

	      auto & operator--(   ) {                   *this -= 1; return *this; }

//  ------------------------------------------------------------------------------------------

	friend auto operator+ (const Ratio & lhs, const Ratio & rhs) { return Ratio(lhs) += rhs; }

	friend auto operator- (const Ratio & lhs, const Ratio & rhs) { return Ratio(lhs) -= rhs; }

	friend auto operator* (const Ratio & lhs, const Ratio & rhs) { return Ratio(lhs) *= rhs; }

	friend auto operator/ (const Ratio & lhs, const Ratio & rhs) { return Ratio(lhs) /= rhs; }

//  ------------------------------------------------------------------------------------------

	friend auto operator< (const Ratio & lhs, const Ratio & rhs)
	{
		return static_cast < double > (lhs) < static_cast < double > (rhs);
	}

	friend auto operator> (const Ratio & lhs, const Ratio & rhs) { return  (rhs < lhs); }
	
	friend auto operator<=(const Ratio & lhs, const Ratio & rhs) { return !(lhs > rhs); }

	friend auto operator>=(const Ratio & lhs, const Ratio & rhs) { return !(lhs < rhs); }

	friend auto operator==(const Ratio & lhs, const Ratio & rhs)
	{
		return !(lhs < rhs) && !(rhs < lhs);
	}

//  ------------------------------------------------------------------------------------------

	friend auto & operator>>(std::istream & stream, Ratio & ratio)
	{
		auto num = 0; auto c = '\0'; auto den = 0; stream >> num >> c >> den;

		if (c != '/') 
		{
			std::cerr << "operator>> : invalid input\n";
		}

		ratio = Ratio(num, den);
		
		return stream;
	}

	friend auto & operator<<(std::ostream & stream, const Ratio & ratio)
	{
		return stream << ratio.m_num << '/' << ratio.m_den;
	}

private:

	void reduce()
	{
		auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;

		m_den /= gcd;
	}

//  ------------------------------------------------------------------------------------------

	int m_num = 0;

	int m_den = 1;
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
		[[maybe_unused]] Ratio ratio_1, ratio_2(2), ratio_3 = 3, ratio_4(4, 1);

//		std::vector < int > vector = 1; // error
	}

//  ---------------------------------------------------------------------------

	{
		Ratio ratio_1 = 1, ratio_2 = 2;

		assert(equal(static_cast < double > (ratio_1), 1.0));

//		assert(ratio_1.operator+=(ratio_2) == Ratio(3, 1)); // bad

		assert((ratio_1 += ratio_2) == Ratio(3, 1));
		assert((ratio_1 +=       1) == Ratio(4, 1));
//		assert((      1 += ratio_2) == Ratio(3, 1)); // error
//		assert((      1 +=       1) == Ratio(2, 1)); // error

		assert((ratio_1 -= ratio_2) == Ratio(2, 1));
		assert((ratio_1 *= ratio_2) == Ratio(4, 1));
		assert((ratio_1 /= ratio_2) == Ratio(2, 1));

		assert((ratio_1 ++        ) == Ratio(2, 1));
		assert((        ++ ratio_2) == Ratio(3, 1));
		assert((ratio_1 --        ) == Ratio(3, 1));
		assert((        -- ratio_2) == Ratio(2, 1));

//		ratio_1++++; // error

//		assert(operator+(ratio_1, ratio_2) == Ratio(4, 1)); // bad

		assert((ratio_1 +  ratio_2) == Ratio(4, 1));
		assert((ratio_1 +        1) == Ratio(3, 1));
		assert((      1 +  ratio_2) == Ratio(3, 1));
		assert((      1 +        1) == Ratio(2, 1));

		assert((ratio_1 -  ratio_2) == Ratio(0, 1));
		assert((ratio_1 *  ratio_2) == Ratio(4, 1));
		assert((ratio_1 /  ratio_2) == Ratio(1, 1));

		assert((ratio_1 <  ratio_2) == 0);
		assert((ratio_1 >  ratio_2) == 0);
		assert((ratio_1 <= ratio_2) == 1);
		assert((ratio_1 >= ratio_2) == 1);
		assert((ratio_1 == ratio_2) == 1);
		assert((ratio_1 != ratio_2) == 0);
	}

//  ---------------------------------------------------------------------------

	{
		std::cout << "main : enter Ratio : "; Ratio ratio; std::cin >> ratio; 
	
		std::cout << "main : ratio = " << ratio << '\n';
	}

//  ---------------------------------------------------------------------------

	{
		boost::rational < int > rational_1 = 1, rational_2 = 2;

		assert(equal(boost::rational_cast < double > (rational_1), 1.0));

		assert((rational_1 += rational_2) == boost::rational < int > (3, 1));
		assert((rational_1 +=          1) == boost::rational < int > (4, 1));
		assert((rational_1 -= rational_2) == boost::rational < int > (2, 1));
		assert((rational_1 *= rational_2) == boost::rational < int > (4, 1));
		assert((rational_1 /= rational_2) == boost::rational < int > (2, 1));

		assert((rational_1 ++           ) == boost::rational < int > (2, 1));
		assert((           ++ rational_2) == boost::rational < int > (3, 1));
		assert((rational_1 --           ) == boost::rational < int > (3, 1));
		assert((           -- rational_2) == boost::rational < int > (2, 1));

		assert((rational_1 +  rational_2) == boost::rational < int > (4, 1));
		assert((rational_1 +           1) == boost::rational < int > (3, 1));
		assert((         1 +  rational_2) == boost::rational < int > (3, 1));
		assert((         1 +           1) == boost::rational < int > (2, 1));

		assert((rational_1 -  rational_2) == boost::rational < int > (0, 1));
		assert((rational_1 *  rational_2) == boost::rational < int > (4, 1));
		assert((rational_1 /  rational_2) == boost::rational < int > (1, 1));

		assert((rational_1 <  rational_2) == 0);
		assert((rational_1 >  rational_2) == 0);
		assert((rational_1 <= rational_2) == 1);
		assert((rational_1 >= rational_2) == 1);
		assert((rational_1 == rational_2) == 1);
		assert((rational_1 != rational_2) == 0);
	}

//  ---------------------------------------------------------------------------

	{
		std::cout << "main : enter boost::rational < int > : "; 
		
		boost::rational < int > rational; std::cin >> rational; 
	
		std::cout << "main : rational = " << rational << '\n';
	}
}