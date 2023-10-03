#include <iostream>
#include <numeric>

class Ratio
{
public:

	using int_t = int;

public:

	/*explicit*/ Ratio(int_t n = 0, int_t d = 1) : // good: no explicit constructor
		m_numerator(n), m_denominator(d) 
	{
		if (m_denominator == 0) // note: primitive error handling
		{
			std::cout << "invalid denominator" << std::endl;
		}

		if (m_denominator < 0) // note: numerator keeps ratio sign
		{
			m_numerator   *= -1;
			m_denominator *= -1;
		}

		reduce();
	}

	explicit operator double() const // good: explicit cast operator
	{
		return 1.0 * m_numerator / m_denominator;
	}

private:

	void reduce()
	{
		auto gcd = std::gcd(m_numerator, m_denominator);

		m_numerator   /= gcd;
		m_denominator /= gcd;
	}

public:

	auto numerator() const
	{
		return m_numerator;
	}

	auto denominator() const
	{
		return m_denominator;
	}

public:

	void print() const // note: function instead of output operator
	{
		std::cout << m_numerator << '/' << m_denominator << std::endl;
	}

public:

	Ratio & operator+=(Ratio other)
	{
		auto lcm = std::lcm(m_denominator, other.m_denominator);

		m_numerator = m_numerator * (lcm /       m_denominator) +
			    other.m_numerator * (lcm / other.m_denominator);

		m_denominator = lcm;

		reduce();

		return *this;
	}

	Ratio & operator-=(Ratio other)
	{
		return (*this += (other.m_numerator *= -1));
	}
		
	Ratio & operator*=(Ratio other)
	{
		m_numerator   *= other.m_numerator;
		m_denominator *= other.m_denominator;

		reduce();

		return *this;
	}
	
	Ratio & operator/=(Ratio other)
	{
		return (*this *= Ratio(other.m_denominator, other.m_numerator));
	}

public:

	Ratio & operator++()
	{
		m_numerator += m_denominator;

		return *this;
	}

	Ratio & operator--()
	{
		m_numerator -= m_denominator;

		return *this;
	}

	Ratio operator++(int)
	{
		Ratio tmp(*this);

		++(*this);

		return tmp;

	}

	Ratio operator--(int)
	{
		Ratio tmp(*this);

		--(*this);

		return tmp;
	}

private:

	int_t m_numerator;
	int_t m_denominator;
};

Ratio operator+(Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs += rhs);
}

Ratio operator-(Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs -= rhs);
}

Ratio operator*(Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs *= rhs);
}

Ratio operator/(Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs /= rhs);
}

bool operator<(Ratio lhs, Ratio rhs)
{
	return static_cast < double > (lhs) < static_cast < double > (rhs);
}

bool operator>(Ratio lhs, Ratio rhs)
{
	return static_cast < double > (lhs) > static_cast < double > (rhs);
}

bool operator>=(Ratio lhs, Ratio rhs)
{
	return !(lhs < rhs);
}

bool operator<=(Ratio lhs, Ratio rhs)
{
	return !(lhs > rhs);
}

bool operator==(Ratio lhs, Ratio rhs)
{
	return (lhs.numerator  () == rhs.numerator  () &&
		    lhs.denominator() == lhs.denominator());
}

bool operator!=(Ratio lhs, Ratio rhs)
{
	return !(lhs == rhs);
}

int main()
{
	Ratio r1;
	Ratio r2(2);
	Ratio r3 = 3;
	Ratio r4(-5, 10);

	std::cout << static_cast < double > (r4) << std::endl;

	(r4 += 10).print();
	(r4 -= r1).print();
	(r4 *= r2).print();
	(r4 /= r3).print();
//	(10 += r4).print(); // error: += not defined for int

	(++r4).print();
	(--r4).print();
	(r4++).print();
	(r4--).print();

	(10 + r4).print(); // note: 10.operator+(r4) do not work
	(r4 - 10).print();
	(r4 * r3).print();
	(r4 / r2).print();
//	(10 / 10).print(); // error: print not defined for int

	std::cout << (r3 < r4) << std::endl;
	std::cout << (r3 > r4) << std::endl;

	std::cout << (r3 <= r4) << std::endl;
	std::cout << (r3 >= r4) << std::endl;

	std::cout << (r3 == r4) << std::endl;
	std::cout << (r3 != r4) << std::endl;

	return 0;
}