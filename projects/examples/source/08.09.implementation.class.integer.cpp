#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <exception>
#include <format>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std::literals;

//////////////////////////////////////////////////////////////////////////////////////////////////

class Integer
{
public:

	using digit_t = long long;

//  --------------------------------------------------------------------------------------------

	Integer() : m_is_negative(false), m_n_digits(1), m_digits(s_size, 0) {}

	Integer(digit_t x) : Integer() 
	{ 
		parse(std::to_string(x)); 
	}

	Integer(const std::string & string) : Integer() 
	{ 
		parse(string); 
	}

//  --------------------------------------------------------------------------------------------

	void swap(Integer & other)
	{
		std::swap(m_is_negative, other.m_is_negative);
		
		std::swap(m_n_digits,    other.m_n_digits   );

		std::swap(m_digits,      other.m_digits     );
	}

//  --------------------------------------------------------------------------------------------

	auto & operator+=(Integer other)
	{
		if 
		(
			(!m_is_negative && !other.m_is_negative) ||
			( m_is_negative &&  other.m_is_negative)
		)
		{
			this->add(other);
		}
		else if (!m_is_negative && other.m_is_negative)
		{
			if (this->less(other))
			{
				*this = std::move(other.subtract(*this)); 
				
				m_is_negative = true;
			}
			else 
			{
				this->subtract(other);
			}
		}
		else if (m_is_negative && !other.m_is_negative)
		{
			if (this->less(other))
			{
				*this = std::move(other.subtract(*this));
			}
			else 
			{ 
				this->subtract(other); m_is_negative = true; 
			}
		}

		return *this;
	}

	auto & operator-=(Integer other)
	{
		other.m_is_negative = !other.m_is_negative;

		return *this += other;
	}

	auto & operator*=(Integer other)
	{
		if (m_n_digits + other.m_n_digits > s_size) 
		{
			throw std::runtime_error("arithmetic overflow");
		}

		Integer result;

		result.m_is_negative = m_is_negative ^ other.m_is_negative;

		for (auto i = 0uz; i < m_n_digits; ++i)
		{
			digit_t r = 0;

			for (auto j = 0uz; (j < other.m_n_digits) || r; ++j)
			{
				result.m_digits[i + j] += m_digits[i] * other.m_digits[j] + r;

				r = result.m_digits[i + j] / s_base;

				result.m_digits[i + j] -= r * s_base;
			}
		}

		result.m_n_digits = m_n_digits + other.m_n_digits;

		swap(result); 
		
		reduce(); 
		
		return *this;
	}

	auto & operator/=(Integer other)
	{
		if (other.m_n_digits == 1 && other.m_digits.front() == 0)
		{
			throw std::runtime_error("invalid operand");
		}

		Integer result; result.m_n_digits = m_n_digits;

		result.m_is_negative = m_is_negative ^ other.m_is_negative; other.m_is_negative = false;

		Integer current;

		for (auto i = static_cast < int > (m_n_digits) - 1; i >= 0; --i)
		{
			current *= s_base; current.m_digits[0] = m_digits[i];

			digit_t l = 0, r = s_base, digit = 0;

			while (l <= r)
			{
				auto m = std::midpoint(l, r);
				
				if (other * m <= current)
				{
					l = m + 1; digit = m;
				}
				else
				{
					r = m - 1;
				}
			}

			result.m_digits[i] = digit; current -= other * digit;
		}

		swap(result); 
		
		reduce(); 
		
		return *this;
	}

//  --------------------------------------------------------------------------------------------

	const auto   operator++(int) { auto copy(*this); *this += 1; return  copy; }

	      auto & operator++(   ) { 				     *this += 1; return *this; }

	const auto   operator--(int) { auto copy(*this); *this -= 1; return  copy; }

	      auto & operator--(   ) { 				     *this -= 1; return *this; }

//  --------------------------------------------------------------------------------------------

	friend auto operator+ (const Integer & lhs, const Integer & rhs) 
	{ 
		return Integer(lhs) += rhs; 
	}

	friend auto operator- (const Integer & lhs, const Integer & rhs) 
	{ 
		return Integer(lhs) -= rhs; 
	}

	friend auto operator* (const Integer & lhs, const Integer & rhs) -> Integer
	{ 
		return Integer(lhs) *= rhs; 
	}

	friend auto operator/ (const Integer & lhs, const Integer & rhs) 
	{ 
		return Integer(lhs) /= rhs; 
	}

//  --------------------------------------------------------------------------------------------

	friend auto operator< (const Integer & lhs, const Integer & rhs)
	{
		if (lhs.m_is_negative != rhs.m_is_negative) { return lhs.m_is_negative; }

		if (lhs.m_is_negative && rhs.m_is_negative) 
		{
			return rhs.less(lhs);
		}
		else
		{
			return lhs.less(rhs);
		}
	}

	friend auto operator> (const Integer & lhs, const Integer & rhs)
	{
		return  (rhs < lhs);
	}

	friend auto operator<=(const Integer & lhs, const Integer & rhs) -> bool
	{
		return !(rhs < lhs);
	}

	friend auto operator>=(const Integer & lhs, const Integer & rhs)
	{
		return !(lhs < rhs);
	}

	friend auto operator==(const Integer & lhs, const Integer & rhs)
	{
		if (lhs.m_is_negative != rhs.m_is_negative || lhs.m_n_digits != rhs.m_n_digits)
		{
			return false;
		}

		for (auto i = 0uz; i < lhs.m_n_digits; ++i)
		{
			if (lhs.m_digits[i] != rhs.m_digits[i]) 
			{
				return false;
			}
		}

		return true;
	}

//  --------------------------------------------------------------------------------------------

	friend auto & operator>>(std::istream & stream, Integer & integer)
	{
		std::string string; stream >> string; 
		
		integer = Integer(string); 
		
		return stream;
	}

	friend auto & operator<<(std::ostream & stream, const Integer & integer)
	{
		if (integer.m_is_negative) 
		{
			stream << '-';
		}

		stream << integer.m_digits[integer.m_n_digits - 1];

		for (auto i = static_cast < int > (integer.m_n_digits) - 2; i >= 0; --i)
		{
			stream << std::format("{:0>{}}", integer.m_digits[i], Integer::s_step);
		}

		return stream;
	}

//  --------------------------------------------------------------------------------------------

	friend auto multiply(const Integer & x, const Integer & y)
	{
		auto n = std::max(x.m_n_digits, y.m_n_digits);

		if (n == 1) 
		{
			return x * y;
		}

		auto k = n / 2;

		Integer xr; xr.m_n_digits = k;

		Integer xl; xl.m_n_digits = n - k;

		for (auto i = 0uz; i < k; ++i) { xr.m_digits[i    ] = x.m_digits[i]; }

		for (auto i = k  ; i < n; ++i) { xl.m_digits[i - k] = x.m_digits[i]; }

		Integer yr; yr.m_n_digits = k;
		
		Integer yl; yl.m_n_digits = n - k;

		for (auto i = 0uz; i < k; ++i) { yr.m_digits[i    ] = y.m_digits[i]; }

		for (auto i = k  ; i < n; ++i) { yl.m_digits[i - k] = y.m_digits[i]; }

		auto p1 = multiply(xl, yl), p2 = multiply(xr, yr), p3 = multiply(xl + xr, yl + yr);

		Integer base = Integer::s_base;

		for (auto i = 1uz; i < k; ++i) 
		{
			base *= Integer::s_base;
		}

		auto result = p1 * base * base + (p3 - p2 - p1) * base + p2;

		result.m_is_negative = x.m_is_negative ^ y.m_is_negative; 

		return result;
	}

//  --------------------------------------------------------------------------------------------

	friend auto sqrt(const Integer & x)
	{
		if (x.m_is_negative) 
		{
			throw std::runtime_error("invalid operand");
		}

    	Integer result; 
		
		result.m_n_digits = (x.m_n_digits + 1) / 2;
    	
    	for (auto i = static_cast < int > (result.m_n_digits) - 1; i >= 0; --i)
    	{
      		digit_t l = 0, r = Integer::s_base, digit = 0;

      		while (l <= r)
      		{
				auto m = result.m_digits[i] = std::midpoint(l, r);

        		if (result * result <= x)
        		{
          			l = m + 1; digit = std::min(m, Integer::s_base - 1);
        		}
        		else
				{
					r = m - 1;
				}				
      		}

      		result.m_digits[i] = digit;
    	}

		result.reduce(); 
		
		return result; 
	}

private:

	void parse(const std::string & string)
	{
		if (string[0] == '+' || string[0] == '-' || std::isdigit(string[0]))
		{
			if (!std::isdigit(string[0]) && std::size(string) == 1)
			{
				throw std::runtime_error("invalid data");
			}

			std::ranges::for_each
			(
				std::next(std::begin(string)), std::end(string), [](auto x)
				{ 
					if (!std::isdigit(x)) 
					{
						throw std::runtime_error("invalid data"); 
					}
				}
			);

			m_is_negative = string[0] == '-'; m_n_digits = 0;

			for (auto i = std::ssize(string) - 1; i >= 0; i -= s_step)
			{
				auto begin = i - s_step + 1;

				if (begin <= 0) 
				{
					begin = m_is_negative ? 1 : 0;
				}

				m_digits[m_n_digits++] = std::stoll(string.substr(begin, i - begin + 1));
			}

			reduce();
		}
		else 
		{
			throw std::runtime_error("invalid data");
		}
	}

//  --------------------------------------------------------------------------------------------

	void reduce()
	{
		while (m_n_digits > 1 && !m_digits[m_n_digits - 1]) 
		{
			--m_n_digits;
		}
	}

//  --------------------------------------------------------------------------------------------

	auto add(const Integer & other) -> Integer &
	{
		m_n_digits = std::max(m_n_digits, other.m_n_digits);

		for (auto i = 0uz; i < m_n_digits; ++i)
		{
			m_digits[i] += other.m_digits[i];

			if (m_digits[i] >= s_base)
			{
				m_digits[i] -= s_base;

				if (i < s_size - 1)
				{
					++m_digits[i + 1];
				}
				else 
				{
					throw std::runtime_error("arithmetic overflow");
				}
			}
		}

		m_n_digits += m_digits[m_n_digits];

		return *this;
	}

	auto subtract(const Integer & other) -> Integer &
	{
		for (auto i = 0uz; i < m_n_digits; ++i)
		{
			m_digits[i] -= other.m_digits[i];

			if (m_digits[i] < 0)
			{
				m_digits[i] += s_base;

				m_digits[i + 1]--;
			}
		}

		reduce(); 
		
		return *this;
	}

//  --------------------------------------------------------------------------------------------

	auto less(const Integer & other) const -> bool
	{
		if (m_n_digits != other.m_n_digits) 
		{
			return m_n_digits < other.m_n_digits;
		}

		for (auto i = static_cast < int > (m_n_digits) - 1; i >= 0; --i)
		{
			if (m_digits[i] != other.m_digits[i]) 
			{
				return m_digits[i] < other.m_digits[i];
			}
		}

		return false;
	}

//  --------------------------------------------------------------------------------------------

	bool m_is_negative = false;

	std::size_t m_n_digits = 0;

	std::vector < digit_t > m_digits; 

//  --------------------------------------------------------------------------------------------

	static inline auto s_size = 1'000uz;

	static inline auto s_step = std::numeric_limits < digit_t > ::digits10 / 2;

	static inline auto s_base = static_cast < digit_t > (std::pow(10, s_step));
};

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		Integer integer_01 = "+73640854127382725310948206095647"s;

		Integer integer_02 = "-46090058756232818791046807807190"s;

		Integer integer_03 = "+27550795371149906519901398288457"s;

		Integer integer_04 = integer_01;

		Integer integer_05 = "-3394111293590239892710602762023649092547630961329778427474301930"s;

		Integer integer_06 = "-46090058756232818791046807807189"s;

		Integer integer_07 = "+73640854127382725310948206095648"s;

		Integer integer_08 = integer_02;

		Integer integer_09 = "+119730912883615544101995013902837"s;

		Integer integer_10 = -1;

		assert((integer_01 += integer_02) == integer_03);
		assert((integer_01 -= integer_02) == integer_04);
		assert((integer_01 *= integer_02) == integer_05);
		assert((integer_01 /= integer_02) == integer_04);

		assert((integer_01 ++           ) == integer_04);
		assert((           ++ integer_02) == integer_06);
		assert((integer_01 --           ) == integer_07);
		assert((           -- integer_02) == integer_08);

		assert((integer_01 +  integer_02) == integer_03);
		assert((integer_01 -  integer_02) == integer_09);
		assert((integer_01 *  integer_02) == integer_05);
		assert((integer_01 /  integer_02) == integer_10);

		assert((integer_01 <  integer_02) == 0);
		assert((integer_01 >  integer_02) == 1);
		assert((integer_01 <= integer_02) == 0);
		assert((integer_01 >= integer_02) == 1);
		assert((integer_01 == integer_02) == 0);
		assert((integer_01 != integer_02) == 1);
	}

//  ----------------------------------------------------------------------------------------------

	{
		std::cout << "main : enter Integer : "; Integer integer; std::cin >> integer; 
	
		std::cout << "main : integer = " << integer << '\n';
	}

//  ----------------------------------------------------------------------------------------------

	{
		Integer integer_1 = "+73640854127382725310948206095647"s;

		Integer integer_2 = "-46090058756232818791046807807190"s;

		Integer integer_3 = "-3394111293590239892710602762023649092547630961329778427474301930"s;

		assert(multiply(integer_1, integer_2) == integer_3);
	}

//  ----------------------------------------------------------------------------------------------

	{
		Integer integer_1 = "+73640854127382725310948206095647"s;

		Integer integer_2 = "+8581424947372244"s;

		assert(sqrt(integer_1) == integer_2);
	}

//  ----------------------------------------------------------------------------------------------

	{
		Integer result = 1; 
		
		for (auto i = 1; i <= 100; ++i) 
		{
			result *= i;
		}

		std::cout << "main : result = " << result << '\n';
	}
}