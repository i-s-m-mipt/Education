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

		Integer x; 
		
		x.m_sign = m_sign ^ other.m_sign;

		for (auto i = 0uz; i < m_size; ++i)
		{
			digit_t remainder = 0;

			for (auto j = 0uz; (j < other.m_size) || remainder; ++j)
			{
				x.m_data[i + j] += m_data[i] * other.m_data[j] + remainder;

				remainder = x.m_data[i + j] / s_base;

				x.m_data[i + j] -= remainder * s_base;
			}
		}

		x.m_size = m_size + other.m_size;

		swap(x); reduce(); 
		
		return *this;
	}

	auto & operator/=(Integer other)
	{
		if (other.m_size == 1 && other.m_data.front() == 0)
		{
			throw std::runtime_error("invalid operand");
		}

		Integer x; 
		
		x.m_size = m_size;

		x.m_sign = m_sign ^ other.m_sign; other.m_sign = false;

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

			x.m_data[i] = digit; current -= other * digit;
		}

		swap(x); reduce(); 
		
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
			auto step = size / 2;

			Integer x1; x1.m_size = step;

			Integer x2; x2.m_size = size - step;

			for (auto i =  0uz; i < step; ++i) { x1.m_data[i       ] = x.m_data[i]; }

			for (auto i = step; i < size; ++i) { x2.m_data[i - step] = x.m_data[i]; }

			Integer y1; y1.m_size = step;
			
			Integer y2; y2.m_size = size - step;

			for (auto i =  0uz; i < step; ++i) { y1.m_data[i       ] = y.m_data[i]; }

			for (auto i = step; i < size; ++i) { y2.m_data[i - step] = y.m_data[i]; }

			auto p1 = multiply(x2, y2);
			
			auto p2 = multiply(x1, y1);
			
			auto p3 = multiply(x2 + x1, y2 + y1);

			Integer base = Integer::s_base;

			for (auto i = 1uz; i < step; ++i) 
			{
				base *= Integer::s_base;
			}

			auto z = p1 * base * base + (p3 - p2 - p1) * base + p2;

			z.m_sign = x.m_sign ^ y.m_sign; 

			return z;
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

    	Integer y; 
		
		y.m_size = (x.m_size + 1) / 2;
    	
    	for (auto i = static_cast < int > (y.m_size) - 1; i >= 0; --i)
    	{
      		digit_t left = 0, right = Integer::s_base, digit = 0;

      		while (left <= right)
      		{
				auto middle = y.m_data[i] = std::midpoint(left, right);

        		if (y * y <= x)
        		{
          			left  = middle + 1; digit = std::min(middle, Integer::s_base - 1);
        		}
        		else
				{
					right = middle - 1;
				}				
      		}

      		y.m_data[i] = digit;
    	}

		y.reduce(); 
		
		return y; 
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
		Integer x = "+73640854127382725310948206095647"s;

		Integer y = "-46090058756232818791046807807190"s;

		Integer integer_1 = "+27550795371149906519901398288457"s;

		Integer integer_2 = x;

		Integer integer_3 = "-3394111293590239892710602762023649092547630961329778427474301930"s;

		Integer integer_4 = "-46090058756232818791046807807189"s;

		Integer integer_5 = "+73640854127382725310948206095648"s;

		Integer integer_6 = y;

		Integer integer_7 = "+119730912883615544101995013902837"s;

		Integer integer_8 = -1;

		assert((x += y) == integer_1);
		assert((x -= y) == integer_2);
		assert((x *= y) == integer_3);
		assert((x /= y) == integer_2);

		assert((x ++  ) == integer_2);
		assert((  ++ y) == integer_4);
		assert((x --  ) == integer_5);
		assert((  -- y) == integer_6);

		assert((x +  y) == integer_1);
		assert((x -  y) == integer_7);
		assert((x *  y) == integer_3);
		assert((x /  y) == integer_8);

		assert((x <  y) == 0);
		assert((x >  y) == 1);
		assert((x <= y) == 0);
		assert((x >= y) == 1);
		assert((x == y) == 0);
		assert((x != y) == 1);
	}

//  ----------------------------------------------------------------------------------------------

	{
		std::cout << "main : enter Integer : "; Integer x; std::cin >> x; 
	
		std::cout << "main : x = " << x << '\n';
	}

//  ----------------------------------------------------------------------------------------------

	{
		assert
		(
			multiply
			(
				Integer("+73640854127382725310948206095647"), 
				
				Integer("-46090058756232818791046807807190")
			)
			== "-3394111293590239892710602762023649092547630961329778427474301930"s
		);
	}

//  ----------------------------------------------------------------------------------------------

	{
		assert(sqrt(Integer("+73640854127382725310948206095647")) == "+8581424947372244"s);
	}

//  ----------------------------------------------------------------------------------------------

	{
		Integer x = 1; 
		
		for (auto i = 1; i <= 100; ++i) 
		{
			x *= i;
		}

		std::cout << "main : x = " << x << '\n';
	}
}