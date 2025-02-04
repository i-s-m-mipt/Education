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

	Integer() : m_sign(false), m_data(s_size, 0), m_size(1) {}

	Integer(digit_t digit) : Integer() 
	{ 
		parse(std::to_string(digit)); 
	}

	Integer(const std::string & string) : Integer() 
	{ 
		parse(string); 
	}

//  --------------------------------------------------------------------------------------------

	void swap(Integer & other)
	{
		std::swap(m_sign, other.m_sign);

		std::swap(m_data, other.m_data);
		
		std::swap(m_size, other.m_size);
	}

//  --------------------------------------------------------------------------------------------

	auto & operator+=(Integer other)
	{
		if ((!m_sign && !other.m_sign) || ( m_sign &&  other.m_sign))
		{
			this->add(other);
		}
		else if (!m_sign && other.m_sign)
		{
			if (this->less(other))
			{
				*this = std::move(other.subtract(*this)); 
				
				m_sign = true;
			}
			else 
			{
				this->subtract(other);
			}
		}
		else if (m_sign && !other.m_sign)
		{
			if (this->less(other))
			{
				*this = std::move(other.subtract(*this));
			}
			else 
			{ 
				this->subtract(other); m_sign = true; 
			}
		}

		return *this;
	}

	auto & operator-=(Integer other)
	{
		other.m_sign = !other.m_sign;

		return *this += other;
	}

	auto & operator*=(Integer other)
	{
		if (m_size + other.m_size > s_size) 
		{
			throw std::runtime_error("arithmetic overflow");
		}

		Integer result;

		result.m_sign = m_sign ^ other.m_sign;

		for (auto i = 0uz; i < m_size; ++i)
		{
			digit_t remainder = 0;

			for (auto j = 0uz; (j < other.m_size) || remainder; ++j)
			{
				result.m_data[i + j] += m_data[i] * other.m_data[j] + remainder;

				remainder = result.m_data[i + j] / s_base;

				result.m_data[i + j] -= remainder * s_base;
			}
		}

		result.m_size = m_size + other.m_size;

		swap(result); 
		
		reduce(); 
		
		return *this;
	}

	auto & operator/=(Integer other)
	{
		if (other.m_size == 1 && other.m_data.front() == 0)
		{
			throw std::runtime_error("invalid operand");
		}

		Integer result; result.m_size = m_size;

		result.m_sign = m_sign ^ other.m_sign; other.m_sign = false;

		Integer current;

		for (auto i = static_cast < int > (m_size) - 1; i >= 0; --i)
		{
			current *= s_base; current.m_data[0] = m_data[i];

			digit_t left = 0, right = s_base, digit = 0;

			while (left <= right)
			{
				if (auto middle = std::midpoint(left, right); other * middle <= current)
				{
					left  = middle + 1; digit = middle;
				}
				else
				{
					right = middle - 1;
				}
			}

			result.m_data[i] = digit; current -= other * digit;
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
		if (lhs.m_sign != rhs.m_sign) { return lhs.m_sign; }

		if (lhs.m_sign && rhs.m_sign) 
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
		if (lhs.m_sign != rhs.m_sign || lhs.m_size != rhs.m_size)
		{
			return false;
		}

		for (auto i = 0uz; i < lhs.m_size; ++i)
		{
			if (lhs.m_data[i] != rhs.m_data[i]) 
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
		if (integer.m_sign) 
		{
			stream << '-';
		}

		stream << integer.m_data[integer.m_size - 1];

		for (auto i = static_cast < int > (integer.m_size) - 2; i >= 0; --i)
		{
			stream << std::format("{:0>{}}", integer.m_data[i], Integer::s_step);
		}

		return stream;
	}

//  --------------------------------------------------------------------------------------------

	friend auto multiply(const Integer & x, const Integer & y) -> Integer
	{
		if (auto size = std::max(x.m_size, y.m_size); size > 1) 
		{
			auto half = size / 2;

			Integer xr; xr.m_size = half;

			Integer xl; xl.m_size = size - half;

			for (auto i =  0uz; i < half; ++i) { xr.m_data[i       ] = x.m_data[i]; }

			for (auto i = half; i < size; ++i) { xl.m_data[i - half] = x.m_data[i]; }

			Integer yr; yr.m_size = half;
			
			Integer yl; yl.m_size = size - half;

			for (auto i =  0uz; i < half; ++i) { yr.m_data[i       ] = y.m_data[i]; }

			for (auto i = half; i < size; ++i) { yl.m_data[i - half] = y.m_data[i]; }

			auto p1 = multiply(xl, yl);
			
			auto p2 = multiply(xr, yr);
			
			auto p3 = multiply(xl + xr, yl + yr);

			Integer base = Integer::s_base;

			for (auto i = 1uz; i < half; ++i) 
			{
				base *= Integer::s_base;
			}

			auto result = p1 * base * base + (p3 - p2 - p1) * base + p2;

			result.m_sign = x.m_sign ^ y.m_sign; 

			return result;
		}
		else
		{
			return x * y;
		}
	}

//  --------------------------------------------------------------------------------------------

	friend auto sqrt(const Integer & x)
	{
		if (x.m_sign) 
		{
			throw std::runtime_error("invalid operand");
		}

    	Integer result; 
		
		result.m_size = (x.m_size + 1) / 2;
    	
    	for (auto i = static_cast < int > (result.m_size) - 1; i >= 0; --i)
    	{
      		digit_t left = 0, right = Integer::s_base, digit = 0;

      		while (left <= right)
      		{
				auto middle = result.m_data[i] = std::midpoint(left, right);

        		if (result * result <= x)
        		{
          			left  = middle + 1; digit = std::min(middle, Integer::s_base - 1);
        		}
        		else
				{
					right = middle - 1;
				}				
      		}

      		result.m_data[i] = digit;
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
				throw std::runtime_error("invalid string");
			}

			std::ranges::for_each
			(
				std::next(std::begin(string)), std::end(string), [](auto x)
				{ 
					if (!std::isdigit(x)) 
					{
						throw std::runtime_error("invalid string"); 
					}
				}
			);

			m_sign = string[0] == '-'; m_size = 0;

			for (auto i = std::ssize(string) - 1; i >= 0; i -= s_step)
			{
				auto begin = i - s_step + 1;

				if (begin <= 0) 
				{
					begin = m_sign ? 1 : 0;
				}

				m_data[m_size++] = std::stoll(string.substr(begin, i - begin + 1));
			}

			reduce();
		}
		else 
		{
			throw std::runtime_error("invalid string");
		}
	}

//  --------------------------------------------------------------------------------------------

	void reduce()
	{
		while (m_size > 1 && !m_data[m_size - 1]) 
		{
			--m_size;
		}
	}

//  --------------------------------------------------------------------------------------------

	auto add(const Integer & other) -> Integer &
	{
		m_size = std::max(m_size, other.m_size);

		for (auto i = 0uz; i < m_size; ++i)
		{
			m_data[i] += other.m_data[i];

			if (m_data[i] >= s_base)
			{
				m_data[i] -= s_base;

				if (i < s_size - 1)
				{
					++m_data[i + 1];
				}
				else 
				{
					throw std::runtime_error("arithmetic overflow");
				}
			}
		}

		m_size += m_data[m_size];

		return *this;
	}

	auto subtract(const Integer & other) -> Integer &
	{
		for (auto i = 0uz; i < m_size; ++i)
		{
			m_data[i] -= other.m_data[i];

			if (m_data[i] < 0)
			{
				m_data[i] += s_base;

				m_data[i + 1]--;
			}
		}

		reduce(); 
		
		return *this;
	}

//  --------------------------------------------------------------------------------------------

	auto less(const Integer & other) const -> bool
	{
		if (m_size != other.m_size) 
		{
			return m_size < other.m_size;
		}

		for (auto i = static_cast < int > (m_size) - 1; i >= 0; --i)
		{
			if (m_data[i] != other.m_data[i]) 
			{
				return m_data[i] < other.m_data[i];
			}
		}

		return false;
	}

//  --------------------------------------------------------------------------------------------

	bool m_sign = false;

	std::vector < digit_t > m_data; 

	std::size_t m_size = 0;

//  --------------------------------------------------------------------------------------------

	static inline auto s_size = 1'000uz;

	static inline auto s_step = std::numeric_limits < digit_t > ::digits10 / 2;

	static inline auto s_base = static_cast < digit_t > (std::pow(10, s_step));
};

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		Integer x01 = "+73640854127382725310948206095647"s;

		Integer x02 = "-46090058756232818791046807807190"s;

		Integer x03 = "+27550795371149906519901398288457"s;

		Integer x04 = x01;

		Integer x05 = "-3394111293590239892710602762023649092547630961329778427474301930"s;

		Integer x06 = "-46090058756232818791046807807189"s;

		Integer x07 = "+73640854127382725310948206095648"s;

		Integer x08 = x02;

		Integer x09 = "+119730912883615544101995013902837"s;

		Integer x10 = -1;

		assert((x01 += x02) == x03);
		assert((x01 -= x02) == x04);
		assert((x01 *= x02) == x05);
		assert((x01 /= x02) == x04);

		assert((x01 ++    ) == x04);
		assert((    ++ x02) == x06);
		assert((x01 --    ) == x07);
		assert((    -- x02) == x08);

		assert((x01 +  x02) == x03);
		assert((x01 -  x02) == x09);
		assert((x01 *  x02) == x05);
		assert((x01 /  x02) == x10);

		assert((x01 <  x02) == 0);
		assert((x01 >  x02) == 1);
		assert((x01 <= x02) == 0);
		assert((x01 >= x02) == 1);
		assert((x01 == x02) == 0);
		assert((x01 != x02) == 1);
	}

//  ----------------------------------------------------------------------------------------------

	{
		std::cout << "main : enter Integer : "; Integer x; std::cin >> x; 
	
		std::cout << "main : x = " << x << '\n';
	}

//  ----------------------------------------------------------------------------------------------

	{
		Integer x = "+73640854127382725310948206095647"s;

		Integer y = "-46090058756232818791046807807190"s;

		Integer z = "-3394111293590239892710602762023649092547630961329778427474301930"s;

		assert(multiply(x, y) == z);
	}

//  ----------------------------------------------------------------------------------------------

	{
		Integer x = "+73640854127382725310948206095647"s;

		Integer y = "+8581424947372244"s;

		assert(sqrt(x) == y);
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