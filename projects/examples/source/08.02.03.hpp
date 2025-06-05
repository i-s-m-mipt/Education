//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <cmath>
#include <cstddef>
#include <format>
#include <istream>
#include <limits>
#include <numeric>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////////

class Integer
{
public :

	using digit_t = long long int;

//  ------------------------------------------------------------------------------------------

	Integer() : m_is_negative(false), m_digits(s_size, 0), m_size(1) {}

//  ------------------------------------------------------------------------------------------

	Integer(digit_t digit) : Integer() 
	{ 
		parse(std::to_string(digit));
	}

//  ------------------------------------------------------------------------------------------

	Integer(std::string const & string) : Integer() 
	{ 
		parse(string);
	}

//  ------------------------------------------------------------------------------------------

	void swap(Integer & other)
	{
		std::swap(m_is_negative, other.m_is_negative);

		std::swap(m_digits,      other.m_digits     );
		
		std::swap(m_size,        other.m_size       );
	}

//  ------------------------------------------------------------------------------------------

	auto & operator+=(Integer other)
	{
		if (m_is_negative == other.m_is_negative)
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
				this->subtract(other);
				
				m_is_negative = true;
			}
		}

		return *this;
	}

//  ------------------------------------------------------------------------------------------

	auto & operator-=(Integer other)
	{
		other.m_is_negative = !other.m_is_negative;

		return *this += other;
	}

//  ------------------------------------------------------------------------------------------

	auto & operator*=(Integer other)
	{
		Integer x;
		
		x.m_is_negative = m_is_negative ^ other.m_is_negative;

		for (auto i = 0uz; i < m_size; ++i)
		{
			digit_t remainder = 0;

			for (auto j = 0uz; (j < other.m_size) || remainder; ++j)
			{
				x.m_digits[i + j] += m_digits[i] * other.m_digits[j] + remainder;

				remainder = x.m_digits[i + j] / s_base;

				x.m_digits[i + j] -= remainder * s_base;
			}
		}

		x.m_size = m_size + other.m_size;

		swap(x);
		
		reduce();
		
		return *this;
	}

//  ------------------------------------------------------------------------------------------

	auto & operator/=(Integer other)
	{
		Integer x;
		
		x.m_size = m_size;

		x.m_is_negative = m_is_negative ^ other.m_is_negative;
		
		other.m_is_negative = false;

		Integer current;

		for (auto i = static_cast < int > (m_size) - 1; i >= 0; --i)
		{
			current *= s_base;
			
			current.m_digits.front() = m_digits[i];

			digit_t left = 0, right = s_base, digit = 0;

			while (left <= right)
			{
				if (auto middle = std::midpoint(left, right); other * middle <= current)
				{
					left  = middle + 1;
					
					digit = middle;
				}
				else
				{
					right = middle - 1;
				}
			}

			x.m_digits[i] = digit;
			
			current -= other * digit;
		}

		swap(x);
		
		reduce();
		
		return *this;
	}

//  ------------------------------------------------------------------------------------------

	auto const operator++(int) { auto x = *this; *this += 1; return x; }

	auto const operator--(int) { auto x = *this; *this -= 1; return x; }

//  ------------------------------------------------------------------------------------------

	auto & operator++() { *this += 1; return *this; }

	auto & operator--() { *this -= 1; return *this; }

//  ------------------------------------------------------------------------------------------

	friend auto operator+ (Integer lhs, Integer const & rhs) 			{ return lhs += rhs; }

	friend auto operator- (Integer lhs, Integer const & rhs) 			{ return lhs -= rhs; }

	friend auto operator* (Integer lhs, Integer const & rhs) -> Integer { return lhs *= rhs; }

	friend auto operator/ (Integer lhs, Integer const & rhs) 			{ return lhs /= rhs; }

//  ------------------------------------------------------------------------------------------

	friend auto operator< (Integer const & lhs, Integer const & rhs)
	{
		if (lhs.m_is_negative != rhs.m_is_negative)
		{ 
			return lhs.m_is_negative; 
		}

		if (lhs.m_is_negative && rhs.m_is_negative)
		{
			return rhs.less(lhs);
		}
		else
		{
			return lhs.less(rhs);
		}
	}

//  ------------------------------------------------------------------------------------------

	friend auto operator> (Integer const & lhs, Integer const & rhs)
	{
		return  (rhs < lhs);
	}

//  ------------------------------------------------------------------------------------------

	friend auto operator<=(Integer const & lhs, Integer const & rhs) -> bool
	{
		return !(rhs < lhs);
	}

//  ------------------------------------------------------------------------------------------

	friend auto operator>=(Integer const & lhs, Integer const & rhs)
	{
		return !(lhs < rhs);
	}

//  ------------------------------------------------------------------------------------------

	friend auto operator==(Integer const & lhs, Integer const & rhs) -> bool
	{
		if (lhs.m_is_negative != rhs.m_is_negative || lhs.m_size != rhs.m_size)
		{
			return false;
		}

		for (auto i = 0uz; i < lhs.m_size; ++i)
		{
			if (lhs.m_digits[i] != rhs.m_digits[i])
			{
				return false;
			}
		}

		return true;
	}

//  ------------------------------------------------------------------------------------------

	friend auto & operator>>(std::istream & stream, Integer & integer)
	{
		std::string string;
		
		stream >> string;
		
		integer = Integer(string);
		
		return stream;
	}

//  ------------------------------------------------------------------------------------------

	friend auto & operator<<(std::ostream & stream, Integer const & integer)
	{
		if (integer.m_is_negative) 
		{
			stream << '-';
		}

		stream << integer.m_digits[integer.m_size - 1];

		for (auto i = static_cast < int > (integer.m_size) - 2; i >= 0; --i)
		{
			stream << std::format("{:0>{}}", integer.m_digits[i], Integer::s_step);
		}

		return stream;
	}

//  ------------------------------------------------------------------------------------------

	friend auto sqrt(Integer const & x)
	{
		Integer y;
		
		y.m_size = (x.m_size + 1) / 2;
		
		for (auto i = static_cast < int > (y.m_size) - 1; i >= 0; --i)
		{
			digit_t left = 0, right = Integer::s_base, digit = 0;

			while (left <= right)
			{
				auto middle = y.m_digits[i] = std::midpoint(left, right);

				if (y * y <= x)
				{
					left  = middle + 1;
					
					digit = std::min(middle, Integer::s_base - 1);
				}
				else
				{
					right = middle - 1;
				}				
			}

			y.m_digits[i] = digit;
		}

		y.reduce();
		
		return y;
	}

//  ------------------------------------------------------------------------------------------

	friend auto multiply(Integer const & x, Integer const & y) -> Integer
	{
		if (auto size = std::max(x.m_size, y.m_size); size > 1)
		{
			auto step = size / 2;

			Integer x1, x2;

			x1.m_size = step;

			x2.m_size = size - step;

			for (auto i =  0uz; i < step; ++i) { x1.m_digits[i       ] = x.m_digits[i]; }

			for (auto i = step; i < size; ++i) { x2.m_digits[i - step] = x.m_digits[i]; }

			Integer y1, y2;

			y1.m_size = step;
			
			y2.m_size = size - step;

			for (auto i =  0uz; i < step; ++i) { y1.m_digits[i       ] = y.m_digits[i]; }

			for (auto i = step; i < size; ++i) { y2.m_digits[i - step] = y.m_digits[i]; }

			auto a = multiply(x2, y2);
			
			auto b = multiply(x1, y1);
			
			auto c = multiply(x2 + x1, y2 + y1);

			Integer base = Integer::s_base;

			for (auto i = 1uz; i < step; ++i)
			{
				base *= Integer::s_base;
			}

			auto z = a * base * base + (c - b - a) * base + b;

			z.m_is_negative = x.m_is_negative ^ y.m_is_negative;

			return z;
		}
		else
		{
			return x * y;
		}
	}

private :

	void parse(std::string const & string)
	{
		m_is_negative = string.front() == '-';
			
		m_size = 0;

		for (auto i = std::ssize(string) - 1; i >= 0; i -= s_step)
		{
			auto begin = std::max(i - s_step + 1, 0l);

			if (begin == 0 && !std::isdigit(string.front()))
			{
				++begin;
			}

			auto digit = string.substr(begin, i - begin + 1);

			if (std::size(digit) > 0)
			{
				m_digits[m_size++] = std::stoll(digit);
			}
		}

		reduce();
	}

//  ------------------------------------------------------------------------------------------

	void reduce()
	{
		while (m_size > 1 && !m_digits[m_size - 1]) 
		{
			--m_size;
		}
	}

//  ------------------------------------------------------------------------------------------

	auto add(Integer const & other) -> Integer &
	{
		m_size = std::max(m_size, other.m_size);

		for (auto i = 0uz; i < m_size; ++i)
		{
			m_digits[i] += other.m_digits[i];

			if (m_digits[i] >= s_base)
			{
				m_digits[i] -= s_base;

				m_digits[i + 1]++;
			}
		}

		m_size += m_digits[m_size];

		return *this;
	}

//  ------------------------------------------------------------------------------------------

	auto subtract(Integer const & other) -> Integer &
	{
		for (auto i = 0uz; i < m_size; ++i)
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

//  ------------------------------------------------------------------------------------------

	auto less(Integer const & other) const -> bool
	{
		if (m_size != other.m_size) 
		{
			return m_size < other.m_size;
		}

		for (auto i = static_cast < int > (m_size) - 1; i >= 0; --i)
		{
			if (m_digits[i] != other.m_digits[i]) 
			{
				return m_digits[i] < other.m_digits[i];
			}
		}

		return false;
	}

//  ------------------------------------------------------------------------------------------

	bool m_is_negative = false;

	std::vector < digit_t > m_digits;

	std::size_t m_size = 0;

//  ------------------------------------------------------------------------------------------

	static inline auto s_size = 1'000uz;

	static inline auto s_step = std::numeric_limits < digit_t > ::digits10 / 2;

	static inline auto s_base = static_cast < digit_t > (std::pow(10, s_step));
};

//////////////////////////////////////////////////////////////////////////////////////////////