#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>

#include <boost/rational.hpp> // support: библиотека gmp_rational

//  ================================================================================================

class Ratio
{
public:

	/*explicit*/ Ratio(int num = 0, int den = 1) : m_num(num), m_den(den)
	{
		if (m_den == 0) std::cerr << "invalid denominator\n";

		if (m_den <  0)
		{
			m_num *= -1;
			m_den *= -1;
		}

		reduce();
	}

	[[nodiscard]] explicit operator double() const { return (1.0 * m_num / m_den); }

private:

	void reduce()
	{
		const auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;
		m_den /= gcd;
	}

public:

	void swap(Ratio & other)
	{
		using std::swap; 

		swap(m_num, other.m_num);
		swap(m_den, other.m_den);
	}

public:

	[[nodiscard]] int num() const { return m_num; }
	[[nodiscard]] int den() const { return m_den; }

public:

	friend std::istream & operator>>(std::istream & stream, Ratio & ratio)
	{
		int num{}; char c{}; int den{};

		stream >> num >> c >> den;

		if (c != '/') std::cerr << "invalid input\n";

		ratio = Ratio(num, den);
		
		return stream;
	}

	friend std::ostream & operator<<(std::ostream & stream, const Ratio & ratio)
	{
		stream << ratio.m_num << '/' << ratio.m_den; return stream;
	}

public:

	Ratio & operator+=(Ratio other)
	{
		const auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den); m_den = lcm;

		reduce();

		return *this;
	}

	Ratio & operator-=(Ratio other) { return (*this += (other.m_num *= -1)); }

public:
		
	Ratio & operator*=(Ratio other)
	{
		m_num *= other.m_num;
		m_den *= other.m_den;

		reduce();

		return *this;
	}
	
	Ratio & operator/=(Ratio other) { return (*this *= Ratio(other.m_den, other.m_num)); }

public:

	Ratio & operator++() { m_num += m_den; return *this; } 
	Ratio & operator--() { m_num -= m_den; return *this; } 

public:

	const Ratio operator++(int) { Ratio t(*this); ++(*this); return t; } 
	const Ratio operator--(int) { Ratio t(*this); --(*this); return t; } 

private:

	int m_num;
	int m_den;

}; // class Ratio

//  ================================================================================================

inline void swap(Ratio & x, Ratio & y) { x.swap(y); }

//  ================================================================================================

[[nodiscard]] inline Ratio operator+(Ratio lhs, Ratio rhs) { return (lhs += rhs); }
[[nodiscard]] inline Ratio operator-(Ratio lhs, Ratio rhs) { return (lhs -= rhs); }
[[nodiscard]] inline Ratio operator*(Ratio lhs, Ratio rhs) { return (lhs *= rhs); }
[[nodiscard]] inline Ratio operator/(Ratio lhs, Ratio rhs) { return (lhs /= rhs); }

//  ================================================================================================

[[nodiscard]] inline bool operator< (Ratio lhs, Ratio rhs)
{
	return static_cast < double > (lhs) < static_cast < double > (rhs);
}

[[nodiscard]] inline bool operator> (Ratio lhs, Ratio rhs) { return  (rhs < lhs); }
[[nodiscard]] inline bool operator<=(Ratio lhs, Ratio rhs) { return !(lhs > rhs); }
[[nodiscard]] inline bool operator>=(Ratio lhs, Ratio rhs) { return !(lhs < rhs); }
[[nodiscard]] inline bool operator==(Ratio lhs, Ratio rhs)
{
	return (!(lhs < rhs) && !(rhs < lhs));
}

//  ================================================================================================

int main()
{
	Ratio ratio_1, ratio_2(2), ratio_3 = 3, ratio_4(-4, 5);

//	std::vector < int > vector = 42; // error

	std::cout << static_cast < double > (ratio_4) << std::endl;

//  ================================================================================================

	Ratio ratio_5{}; std::cin >> ratio_5; std::cout << ratio_5 << std::endl;

//  ================================================================================================

	std::cout << (ratio_4 +=       1) << std::endl;
	std::cout << (ratio_4 -= ratio_1) << std::endl;
	std::cout << (ratio_4 *= ratio_2) << std::endl;
	std::cout << (ratio_4 /= ratio_3) << std::endl;
//	std::cout << (      1 += ratio_4) << std::endl; // error

	std::cout << ratio_4.operator+=(ratio_1) << std::endl;

//  ================================================================================================

	std::cout << (++ratio_4  ) << std::endl;
	std::cout << (--ratio_4  ) << std::endl;
	std::cout << (  ratio_4++) << std::endl;
	std::cout << (  ratio_4--) << std::endl;

//  ================================================================================================

	std::cout << (      1 + ratio_4) << std::endl;
	std::cout << (ratio_4 -       1) << std::endl;
	std::cout << (ratio_4 * ratio_3) << std::endl;
	std::cout << (ratio_4 / ratio_2) << std::endl;
	std::cout << (      1 /       1) << std::endl;

	std::cout << operator+(ratio_4, ratio_1) << std::endl;

//  ================================================================================================

	std::cout << (ratio_3 <  ratio_4) << std::endl;
	std::cout << (ratio_3 >  ratio_4) << std::endl;
	std::cout << (ratio_3 <= ratio_4) << std::endl;
	std::cout << (ratio_3 >= ratio_4) << std::endl;
	std::cout << (ratio_3 == ratio_4) << std::endl;
	std::cout << (ratio_3 != ratio_4) << std::endl;

//  ================================================================================================

	boost::rational < int > ratio_6(2, 5);
	boost::rational < int > ratio_7(3, 7);

	std::cout << boost::rational < int > (5, 10) << std::endl;

	std::cout << (ratio_6 + ratio_7) << std::endl;
	std::cout << (ratio_6 - ratio_7) << std::endl;
	std::cout << (ratio_6 * ratio_7) << std::endl;
	std::cout << (ratio_6 / ratio_7) << std::endl;

	std::cout << boost::rational_cast < int    > (ratio_6) << std::endl;
    std::cout << boost::rational_cast < double > (ratio_7) << std::endl;

	return 0;
}