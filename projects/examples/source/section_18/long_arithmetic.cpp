#include <cassert>
#include <cctype>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <istream>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

using namespace std::literals;

class Big_Int
{
public:

	using digit_t = long long; // note: 8 byte(s) at least

public:

	Big_Int() : m_is_negative(false), m_n_digits(1), m_digits(size, 0) {}

	Big_Int(digit_t number) : Big_Int() { parse(std::to_string(number)); }

	Big_Int(std::string string) : Big_Int() { parse(std::move(string)); }

private:

	void parse(std::string && string)
	{
		if (string[0] == '+' || string[0] == '-' || std::isdigit(string[0]))
		{
			if (!std::isdigit(string[0]) && std::size(string) == 1)
			{
				throw std::runtime_error("invalid input: "s + string[0]);
			}

			for (std::size_t i = 1; i < std::size(string); ++i)
			{
				if (!std::isdigit(string[i]))
				{
					throw std::runtime_error("invalid input: "s + string[i]);
				}
			}

			m_is_negative = (string[0] == '-'); m_n_digits = 0;

			for (auto i = static_cast < int > (std::size(string)) - 1; i >= 0; i -= step)
			{
				auto start = i - step + 1;

				if (start <= 0) start = (m_is_negative ? 1 : 0);

				m_digits[m_n_digits++] = std::stoll(string.substr(start, i - start + 1));
			}

			for (; m_n_digits > 1 && !m_digits[m_n_digits - 1]; --m_n_digits);
		}
		else throw std::runtime_error("invalid input: "s + string[0]);
	}

public:

	void swap(Big_Int & other) noexcept
	{
		using std::swap; // good: enable argument-dependent lookup

		swap(m_is_negative, other.m_is_negative);
		swap(m_n_digits,    other.m_n_digits   );
		swap(m_digits,      other.m_digits     );
	}

public:

	friend std::istream & operator>>(std::istream & stream,       Big_Int & big_int)
	{
		std::string s; stream >> s; big_int = Big_Int(s); return stream;
	}

	friend std::ostream & operator<<(std::ostream & stream, const Big_Int & big_int)
	{
		if (big_int.m_is_negative) stream << '-';

		stream << big_int.m_digits[big_int.m_n_digits - 1];

		for (auto i = static_cast < int > (big_int.m_n_digits) - 2; i >= 0; --i)
		{
			stream << std::setw(step) << std::setfill('0') << big_int.m_digits[i];
		}

		return stream;
	}

public:

	auto & operator+=(Big_Int other)
	{
		if ((!m_is_negative && !other.m_is_negative) ||
			( m_is_negative &&  other.m_is_negative))
		{
			this->unsigned_add(other);
		}
		else if (!m_is_negative && other.m_is_negative)
		{
			if (this->unsigned_less(other))
			{
				*this = std::move(other.unsigned_sub(*this)); 
				
				m_is_negative = true;
			}
			else
			{
				this->unsigned_sub(other);
			}
		}
		else if (m_is_negative && !other.m_is_negative)
		{
			if (this->unsigned_less(other))
			{
				*this = std::move(other.unsigned_sub(*this));
			}
			else
			{
				this->unsigned_sub(other); 
				
				m_is_negative = true;
			}
		}

		return *this;
	}

	auto & operator-=(Big_Int other)
	{
		other.m_is_negative = !other.m_is_negative;

		return (*this += other);
	}

	auto & operator*=(Big_Int other)
	{
		if (m_n_digits + other.m_n_digits > size) throw std::overflow_error("too many digits");

		Big_Int result;

		result.m_is_negative = m_is_negative ^ other.m_is_negative;

		for (std::size_t i = 0; i < m_n_digits; ++i)
		{
			digit_t r = 0;

			for (std::size_t j = 0; (j < other.m_n_digits) || r; ++j)
			{
				result.m_digits[i + j] += (m_digits[i] * other.m_digits[j] + r);

				r = result.m_digits[i + j] / Big_Int::base;

				result.m_digits[i + j] -= (r * Big_Int::base);
			}
		}

		result.m_n_digits = m_n_digits + other.m_n_digits;

		for (; result.m_n_digits > 1 && !result.m_digits[result.m_n_digits - 1]; --result.m_n_digits);

		swap(result); return *this;
	}

	auto & operator/=(Big_Int other)
	{
		if (other.m_n_digits == 0 || (other.m_n_digits == 1 && other.m_digits.front() == 0))
		{
			throw std::runtime_error("division by zero");
		}

		Big_Int result;

		result.m_is_negative = m_is_negative ^ other.m_is_negative; 
		
		other.m_is_negative = false;

		Big_Int current;

		for (auto i = static_cast < int > (m_n_digits) - 1; i >= 0; --i)
		{
			current *= Big_Int::base; current.m_digits[0] = m_digits[i];

			digit_t l = 0, r = Big_Int::base, x = 0;

			while (l <= r)
			{
				auto m = std::midpoint(l, r);

				if (Big_Int t(other); (t *= m) <= current)
				{
					l = m + 1; x = m;
				}
				else
				{
					r = m - 1;
				}
			}

			result.m_digits[i] = x; Big_Int t(other); current -= (t *= x);
		}

		result.m_n_digits = m_n_digits;

		for (; result.m_n_digits > 1 && !result.m_digits[result.m_n_digits - 1]; --result.m_n_digits);

		swap(result); return *this;
	}

private:

	Big_Int & unsigned_add(const Big_Int & other)
	{
		m_n_digits = std::max(m_n_digits, other.m_n_digits);

		for (std::size_t i = 0; i < m_n_digits; ++i)
		{
			if (m_digits[i] += other.m_digits[i]; m_digits[i] >= Big_Int::base)
			{
				if (m_digits[i] -= Big_Int::base; i < size - 1)
				{
					++m_digits[i + 1];
				}
				else throw std::overflow_error("too many digits");
			}
		}

		m_n_digits += (m_digits[m_n_digits]);

		return *this;
	}

	Big_Int & unsigned_sub(const Big_Int & other) noexcept
	{
		for (std::size_t i = 0; i < m_n_digits; ++i)
		{
			if (m_digits[i] -= other.m_digits[i]; m_digits[i] < 0)
			{
				m_digits[i] += Big_Int::base;

				m_digits[i + 1]--;
			}
		}

		for (; m_n_digits > 1 && !m_digits[m_n_digits - 1]; --m_n_digits);

		return *this;
	}

public:

	auto & operator++() { *this += 1; return *this; }
	auto & operator--() { *this -= 1; return *this; }

	const auto operator++(int)
	{
		Big_Int t(*this); ++(*this); return t;
	}

	const auto operator--(int)
	{
		Big_Int t(*this); --(*this); return t;
	}

public:

	[[nodiscard]] friend const bool operator< (const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		if ( lhs.m_is_negative && !rhs.m_is_negative) return 1;
		if (!lhs.m_is_negative &&  rhs.m_is_negative) return 0;

		if (!lhs.m_is_negative && !rhs.m_is_negative) 
		{
			return lhs.unsigned_less(rhs);
		}
		else
		{
			return rhs.unsigned_less(lhs);
		}
	}

	[[nodiscard]] friend const bool operator> (const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return (rhs < lhs);
	}

	[[nodiscard]] friend const bool operator<=(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return !(rhs < lhs);
	}

	[[nodiscard]] friend const bool operator>=(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return !(lhs < rhs);
	}

	[[nodiscard]] friend const bool operator==(const Big_Int & lhs, const Big_Int & rhs) noexcept
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

	[[nodiscard]] bool unsigned_less(const Big_Int & other) const noexcept
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

	std::vector < digit_t > m_digits; 

}; // class Big_Int

void swap(Big_Int & x, Big_Int & y) noexcept { x.swap(y); }

[[nodiscard]] inline const auto operator+(Big_Int lhs, Big_Int rhs) { return (lhs += rhs); }
[[nodiscard]] inline const auto operator-(Big_Int lhs, Big_Int rhs) { return (lhs -= rhs); }
[[nodiscard]] inline const auto operator*(Big_Int lhs, Big_Int rhs) { return (lhs *= rhs); }
[[nodiscard]] inline const auto operator/(Big_Int lhs, Big_Int rhs) { return (lhs /= rhs); }

/*


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

*/

int main()
{
	try
	{
		Big_Int bi1;
		Big_Int bi2 = 42;
		Big_Int bi3 = "-1234567890"s;

		std::cin >> bi1; std::cout << bi1 << std::endl;

		assert(bi3 + bi3 == "-2469135780"s);
		assert(bi3 - bi3 == "-0"s);
		assert(bi3 * bi3 == "+1524157875019052100"s);
		assert(bi3 / bi3 == "+1"s);

		assert(++bi3 == "-1234567889"s);
		assert(--bi3 == "-1234567890"s);
		assert(bi3++ == "-1234567890"s); 
		assert(bi3-- == "-1234567889"s);

		assert(bi3 <  bi2);
		assert(bi2 >  bi3);
		assert(bi3 <= bi2);
		assert(bi2 >= bi3);
		assert(bi2 != bi3);

		Big_Int result(1); for (auto i = 1; i < 101; ++i) result *= i;

		std::cout << result << std::endl;

		return EXIT_SUCCESS;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n';

		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "unknown exception\n";

		return EXIT_FAILURE;
	}
}