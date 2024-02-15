#include <iostream>
#include <numeric>

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

	void print() const // note: function instead of output operator
	{
		std::cout << m_num << '/' << m_den << std::endl;
	}

public:

	auto & operator+=(Ratio other)
	{
		auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);

		m_den = lcm;

		reduce();

		return *this;
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
	Ratio r1;
	Ratio r2(2);
	Ratio r3 = 3;
	Ratio r4(-5, 10);

	std::cout << static_cast < double > (r4) << std::endl;

//	std::vector < int > v = 42; // error: no non-explicit constructor

	(r4 += 10).print();
	(r4 -= r1).print();
	(r4 *= r2).print();
	(r4 /= r3).print();
//	(10 += r4).print(); // error: += not defined for int

	r4.operator+=(r1).print(); // note: function-like style

	(++r4).print();
	(--r4).print();
	(r4++).print();
	(r4--).print();

	(10 + r4).print(); // note: 10.operator+(r4) do not work
	(r4 - 10).print();
	(r4 * r3).print();
	(r4 / r2).print();
//	(10 / 10).print(); // error: print not defined for int

	operator+(r4, r1).print(); // note: function-like style

	std::cout << (r3 <  r4) << std::endl;
	std::cout << (r3 >  r4) << std::endl;
	std::cout << (r3 <= r4) << std::endl;
	std::cout << (r3 >= r4) << std::endl;
	std::cout << (r3 == r4) << std::endl;
	std::cout << (r3 != r4) << std::endl;

	return 0;
}