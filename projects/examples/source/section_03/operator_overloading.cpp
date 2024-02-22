#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>

#include <boost/rational.hpp> // note: boost::multiprecision::gmp_rational is faster

class Ratio
{
public:

	/*explicit*/ Ratio(int num = 0, int den = 1) : m_num(num), m_den(den) 
	{
		if (m_den == 0) // note: primitive error handling
		{
			std::cerr << "invalid denominator" << std::endl;
		}

		if (m_den <  0) // note: numerator keeps ratio sign
		{
			m_num *= -1;
			m_den *= -1;
		}

		reduce();
	}

	[[nodiscard]] explicit operator double() const // good: explicit cast operator
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

	void swap(Ratio & other)
	{
		using std::swap; // good: enable argument-dependent lookup

		swap(m_num, other.m_num);
		swap(m_den, other.m_den);
	}

public:

	[[nodiscard]] auto num() const { return m_num; }
	[[nodiscard]] auto den() const { return m_den; }

public:

	friend std::istream & operator>>(std::istream & stream,       Ratio & ratio) // note: not member
	{
		int num{}, den{}; char c{};

		stream >> num >> c >> den;

		if (c != '/') std::cerr << "invalid input" << std::endl; // note: consider also stream states

		ratio = Ratio(num, den);
		
		return stream; // good: chain of calls
	}

	friend std::ostream & operator<<(std::ostream & stream, const Ratio & ratio) // note: not member
	{
		stream << ratio.m_num << '/' << ratio.m_den;
		
		return stream; // good: chain of calls
	}

public:

	auto & operator+=(Ratio other)
	{
		auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);

		m_den = lcm;

		reduce();

		return *this; // good: chain of calls
	}

	auto & operator-=(Ratio other)
	{
		return (*this += (other.m_num *= -1));
	}
		
	auto & operator*=(Ratio other)
	{
		m_num *= other.m_num;
		m_den *= other.m_den;

		reduce();

		return *this;
	}
	
	auto & operator/=(Ratio other)
	{
		return (*this *= Ratio(other.m_den, other.m_num));
	}

public:

	auto & operator++() // note: ++++r is allowed
	{ 
		m_num += m_den; return *this; 
	} 

	auto & operator--() // note: ----r is allowed
	{ 
		m_num -= m_den; return *this; 
	} 

	const auto operator++(int) // note: r++++ is not allowed
	{ 
		Ratio t(*this); ++(*this); return t; 
	} 

	const auto operator--(int) // note: r---- is not allowed
	{ 
		Ratio t(*this); --(*this); return t; 
	} 

private:

	int m_num;
	int m_den;

}; // class Ratio

void swap(Ratio & x, Ratio & y) { x.swap(y); }

[[nodiscard]] inline const auto operator+ (Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs += rhs);
}

[[nodiscard]] inline const auto operator- (Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs -= rhs);
}

[[nodiscard]] inline const auto operator* (Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs *= rhs);
}

[[nodiscard]] inline const auto operator/ (Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs /= rhs);
}

[[nodiscard]] inline const auto operator< (Ratio lhs, Ratio rhs)
{
	return static_cast < double > (lhs) < static_cast < double > (rhs);
}

[[nodiscard]] inline const auto operator> (Ratio lhs, Ratio rhs)
{
	return (rhs < lhs);
}

[[nodiscard]] inline const auto operator<=(Ratio lhs, Ratio rhs)
{
	return !(lhs > rhs);
}

[[nodiscard]] inline const auto operator>=(Ratio lhs, Ratio rhs)
{
	return !(lhs < rhs);
}

[[nodiscard]] inline const auto operator==(Ratio lhs, Ratio rhs) // note: operator!= not required
{
	return (!(lhs < rhs) && !(rhs < lhs));
}

int main()
{
	Ratio r1, r2(2), r3 = 3, r4(-5, 10), r5; // note: implicit conversion for r3

	std::cout << static_cast < double > (r4) << std::endl;

	std::cin >> r5; // note: enter like 1/2

	std::cout << r5 << std::endl;

//	std::vector < int > v = 42; // error: no non-explicit constructor

	std::cout << (r4 += 10) << std::endl;
	std::cout << (r4 -= r1) << std::endl;
	std::cout << (r4 *= r2) << std::endl;
	std::cout << (r4 /= r3) << std::endl;
//	std::cout << (10 += r4) << std::endl; // error: += not defined for prvalue int

	std::cout << r4.operator+=(r1) << std::endl; // note: function-like style

	std::cout << (++r4) << std::endl;
	std::cout << (--r4) << std::endl;
	std::cout << (r4++) << std::endl;
	std::cout << (r4--) << std::endl;

	std::cout << (10 + r4) << std::endl; // note: 10.operator+(r4) do not work
	std::cout << (r4 - 10) << std::endl;
	std::cout << (r4 * r3) << std::endl;
	std::cout << (r4 / r2) << std::endl;
	std::cout << (10 / 10) << std::endl; // note: integer division without Ratio

	std::cout << operator+(r4, r1) << std::endl; // note: function-like style

	std::cout << (r3 <  r4) << std::endl;
	std::cout << (r3 >  r4) << std::endl;
	std::cout << (r3 <= r4) << std::endl;
	std::cout << (r3 >= r4) << std::endl;
	std::cout << (r3 == r4) << std::endl;
	std::cout << (r3 != r4) << std::endl;

	boost::rational < int > br1(2, 5); // note: ignore templates here
	boost::rational < int > br2(3, 7); // note: ignore templates here

	std::cout << boost::rational < int > (5, 10) << std::endl; // note: outputs 1/2

	std::cout << br1 + br2 << std::endl;
	std::cout << br1 - br2 << std::endl;
	std::cout << br1 * br2 << std::endl;
	std::cout << br1 / br2 << std::endl; // note: and many other operations...

	std::cout << boost::rational_cast < int    > (br1) << std::endl;
    std::cout << boost::rational_cast < double > (br2) << std::endl;

	return 0;
}