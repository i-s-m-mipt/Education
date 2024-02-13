#include <cctype>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

class Big_Int
{
public:

	using digit_t = unsigned long long; // note: 8 byte(s) at least

public:

	Big_Int() : m_is_negative(false), m_n_digits(0), m_digits(size, 0) {}

	Big_Int(int number) : Big_Int() { parse(std::to_string(number)); }

	Big_Int(const std::string & string) : Big_Int() { parse(string); }
    
private:

	void parse(const std::string & string)
	{
		m_is_negative = (string[0] == '-');

		for (auto i = static_cast < int > (std::size(string)) - 1; i >= 0; i -= step)
		{
			auto start = i - step + 1;

			if (start <= 0) start = (m_is_negative ? 1 : 0);

			m_digits[m_n_digits++] = std::stoull(string.substr(start, i - start + 1));
		}
	}

public:

	[[nodiscard]] bool is_negative() const noexcept { return m_is_negative; }

public:

	friend std::istream & operator>>(std::istream & stream, Big_Int & big_int)
	{
		std::string s; stream >> s;

		if (std::empty(s) || (s[0] != '+' && s[0] != '-' && !std::isdigit(s[0])))
		{
			throw std::runtime_error("invalid input");
		}

		for (std::size_t i = 1; i < std::size(s); ++i)
		{
			if (!std::isdigit(s[i])) throw std::runtime_error("invalid input");
		}

		big_int = Big_Int(s);

		return stream;
	}

	friend std::ostream & operator<<(std::ostream & stream, const Big_Int & big_int)
	{
		stream << (big_int.m_is_negative ? '-' : '+') << big_int.m_digits.back();

		for (auto i = static_cast < int > (big_int.m_n_digits) - 2; i >= 0; --i)
		{
			stream << std::setfill('0') << std::setw(step) << big_int.m_digits[i];
		}

		return stream;
	}

public:

	[[nodiscard]] friend auto operator<(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		if ( lhs.m_is_negative && !rhs.m_is_negative) return true;
		if (!lhs.m_is_negative &&  rhs.m_is_negative) return false;

		if (!lhs.m_is_negative && !rhs.m_is_negative) return lhs.less(rhs);
		if ( lhs.m_is_negative &&  rhs.m_is_negative) return rhs.less(lhs);
	}

	[[nodiscard]] friend auto operator>(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return (rhs < lhs);
	}

	[[nodiscard]] friend auto operator<=(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return !(rhs < lhs);
	}

	[[nodiscard]] friend auto operator>=(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return !(lhs < rhs);
	}

	[[nodiscard]] friend auto operator==(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		if ((lhs.m_is_negative != rhs.m_is_negative) || (lhs.m_n_digits != rhs.m_n_digits))
		{
			return false;
		}

		for (std::size_t i = 0; i < lhs.m_n_digits; ++i)
		{
			if (lhs.m_digits[i] != rhs.m_digits[i]) return false;
		}

		return true;
	}

private:

	[[nodiscard]] bool less(const Big_Int & other) const noexcept
	{
		if (m_n_digits != other.m_n_digits) return (m_n_digits < other.m_n_digits);

		for (auto i = static_cast < int > (m_n_digits) - 1; i >= 0; --i)
		{
			if (m_digits[i] != other.m_digits[i]) return (m_digits[i] < other.m_digits[i]);
		}

		return false;
	}

private:

	static inline const auto step = std::numeric_limits < digit_t > ::digits10 / 2;

	static inline const auto base = static_cast < digit_t > (std::pow(10, step));

	static inline const std::size_t size = 1'000; // note: maximum number of digits

private:

	bool m_is_negative;

	std::size_t m_n_digits;

	std::vector < unsigned long long > m_digits; 

}; // class Big_Int




	// Math operators ===========================================================================================

	auto operator-(const Big_Int& lhs, const Big_Int& rhs) noexcept
	{
		Big_Int result;

		if (!lhs.m_is_negative && !rhs.m_is_negative)
		{
			if (lhs >= rhs)
			{
				result = detail::subtraction(lhs, rhs);
			}
			else
			{
				result = detail::subtraction(rhs, lhs);
				result.m_is_negative = true;
			}
		}

		if (!lhs.m_is_negative && rhs.m_is_negative)
		{
			result = detail::addition(rhs, lhs);
		}

		if (lhs.m_is_negative && !rhs.m_is_negative)
		{
			result = detail::addition(rhs, lhs);
			result.m_is_negative = true;
		}

		if (lhs.m_is_negative && rhs.m_is_negative)
		{
			if (lhs < rhs)
			{
				result = detail::subtraction(lhs, rhs);
				result.m_is_negative = true;
			}
			else
			{
				result = detail::subtraction(rhs, lhs);
			}
		}

		return result;
	}

	auto operator+(const Big_Int& lhs, const Big_Int& rhs) noexcept
	{
		Big_Int result;

		if (!lhs.m_is_negative && !rhs.m_is_negative)
		{
			result = detail::addition(lhs, rhs);
		}

		if (!lhs.m_is_negative && rhs.m_is_negative)
		{
			if (!detail::greater(rhs, lhs))
			{
				result = detail::subtraction(lhs, rhs);
			}
			else
			{
				result = detail::subtraction(rhs, lhs);
				result.m_is_negative = true;
			}
		}

		if (lhs.m_is_negative && !rhs.m_is_negative)
		{
			if (!detail::greater(lhs, rhs))
			{
				result = detail::subtraction(rhs, lhs);
			}
			else
			{
				result = detail::subtraction(lhs, rhs);
				result.m_is_negative = true;
			}
		}

		if (lhs.m_is_negative && rhs.m_is_negative)
		{
			result = detail::addition(lhs, rhs);
			result.m_is_negative = true;
		}

		return result;
	}

	auto operator*(const Big_Int& lhs, const Big_Int& rhs) noexcept
	{
		Big_Int result;

		result.m_is_negative = lhs.m_is_negative ^ rhs.m_is_negative;

		for (std::size_t i = 0; i < lhs.m_n_digits; ++i)
		{
			unsigned int r = 0;

			for (std::size_t j = 0; (j < rhs.m_n_digits) || r; ++j)
			{
				result.digits[i + j] += (lhs.digits[i] * rhs.digits[j] + r);

				r = result.digits[i + j] / Big_Int::base;

				result.digits[i + j] -= (r * Big_Int::base);
			}
		}

		std::size_t position = lhs.m_n_digits + rhs.m_n_digits;

		while (position > 0 && !result.digits[position])
		{
			--position;
		}

		result.m_n_digits = position + 1;

		return result;
	};

	auto karatsuba_multiply(const Big_Int& x, const Big_Int& y) noexcept
	{
		auto n = std::max(x.m_n_digits, y.m_n_digits);

		if (n == 1)
		{
			return x * y;
		}

		std::size_t k = n / 2;

		Big_Int xr;
		Big_Int xl;

		xr.m_n_digits = k;
		xl.m_n_digits = n - k;

		for (std::size_t i = 0; i < k; ++i)
		{
			xr.digits[i] = x.digits[i];
		}
		for (std::size_t i = n / 2; i < n; ++i)
		{
			xl.digits[i - k] = x.digits[i];
		}

		Big_Int yr;
		Big_Int yl;

		yr.m_n_digits = k;
		yl.m_n_digits = n - k;

		for (std::size_t i = 0; i < n / 2; ++i)
		{
			yr.digits[i] = y.digits[i];
		}
		for (std::size_t i = k; i < n; ++i)
		{
			yl.digits[i - k] = y.digits[i];
		}

		Big_Int p1 = karatsuba_multiply(xl, yl);
		Big_Int p2 = karatsuba_multiply(xr, yr);
		Big_Int p3 = karatsuba_multiply(xl + xr, yl + yr);

		Big_Int bases = Big_Int::base;

		for (std::size_t i = 1; i < n / 2; ++i)
		{
			bases = bases * Big_Int(Big_Int::base);
		}

		Big_Int result = p1 * bases * bases + (p3 - p2 - p1) * bases + p2;

		return result;
	}

	Big_Int operator/(const Big_Int& lhs, const Big_Int& rhs) noexcept
	{
		if (rhs.digits[0] == 0)
		{
			throw Big_Int_Error("error: division by zero");
		}

		Big_Int result;

		result.m_is_negative = lhs.m_is_negative ^ rhs.m_is_negative;

		Big_Int current;

		for (int i = lhs.m_n_digits - 1; i >= 0; --i)
		{
			current = current * Big_Int(Big_Int::base);

			current.digits[0] = lhs.digits[i];

			int x = 0;

			int l = 0;
			int r = Big_Int::base;

			while (l <= r)
			{
				int m = (l + r) >> 1;

				Big_Int temp = rhs * Big_Int(m);

				if (temp <= current)
				{
					x = m;
					l = m + 1;
				}
				else
				{
					r = m - 1;
				}

			}

			result.digits[i] = x;
			current = current - rhs * x;
		}

		int position = lhs.m_n_digits;

		while (position > 0 && !result.digits[position])
		{
			--position;
		}

		result.m_n_digits = position + 1;

		return result;
	}

namespace detail
{
	ariphmetic::Big_Int addition(const ariphmetic::Big_Int& lhs, const ariphmetic::Big_Int& rhs) noexcept
	{
		ariphmetic::Big_Int result;

		result.m_n_digits = std::max(lhs.m_n_digits, rhs.m_n_digits);

		for (std::size_t i = 0; i < result.m_n_digits; ++i)
		{
			result.digits[i] += (lhs.digits[i] + rhs.digits[i]);

			if (result.digits[i] >= ariphmetic::Big_Int::base)
			{
				result.digits[i] -= ariphmetic::Big_Int::base;
				result.digits[i + 1]++;
			}
		}

		if (result.digits[result.m_n_digits])
		{
			result.m_n_digits++;
		}

		return result;
	}

	ariphmetic::Big_Int subtraction(const ariphmetic::Big_Int& lhs, const ariphmetic::Big_Int& rhs) noexcept
	{
		ariphmetic::Big_Int result = lhs;

		result.m_is_negative = false;

		for (std::size_t i = 0; i < result.m_n_digits; ++i)
		{
			result.digits[i] = result.digits[i] - rhs.digits[i];

			if (result.digits[i] < 0)
			{
				result.digits[i] += ariphmetic::Big_Int::base;
				result.digits[i + 1]--;
			}
		}

		int position = result.m_n_digits;

		while (position > 0 && !result.digits[position])
		{
			--position;
		}

		result.m_n_digits = position + 1;

		return result;
	}
}

int main() try
{
	ariphmetic::Big_Int num1(100500);
	ariphmetic::Big_Int num2(100);

	std::cout << num1 + num2 << std::endl;
	std::cout << num1 / num2 << std::endl;

	ariphmetic::Big_Int num3;
	ariphmetic::Big_Int num4;
	std::cin >> num3 >> num4;

	std::cout << num3 + num4 << std::endl;
	std::cout << num3 / num4 << std::endl; // abort() is called if num4 == 0; alternatively we can return inf?..

	return 0;
}
catch (const ariphmetic::Big_Int_Error& exception)
{
	std::cerr << exception.what() << std::endl;
	return 0;
}
catch (const std::exception& exception)
{
	std::cerr << exception.what() << std::endl;
	return 0;
}
catch (...)
{
	std::cerr << "there is an exception" << std::endl;
	return 0;
}