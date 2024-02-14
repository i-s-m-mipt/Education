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
#include <type_traits>
#include <vector>

class Big_Int
{
public:

	using digit_t = long long; // note: 8 byte(s) at least

public:

	Big_Int() : m_is_negative(false), m_n_digits(0), m_digits(size, 0) {}

	Big_Int(int number) : Big_Int() { parse(std::to_string(number)); }

	Big_Int(std::string string) : Big_Int() { parse(std::move(string)); }
    
private:

	void parse(std::string && string)
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

	friend std::istream & operator>>(std::istream & stream,       Big_Int & big_int)
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
		if (big_int.m_is_negative) stream << '-';

		stream << big_int.m_digits[big_int.m_n_digits - 1];

		for (auto i = static_cast < int > (big_int.m_n_digits) - 2; i >= 0; --i)
		{
			stream << std::setfill('0') << std::setw(step) << big_int.m_digits[i];
		}

		return stream;
	}

public:

	auto & operator+=(Big_Int other)
	{
		if (!m_is_negative && !other.m_is_negative)
		{
			*this = unsigned_add(std::move(*this), std::move(other));
		}
		else
		if ( m_is_negative &&  other.m_is_negative)
		{
			*this = unsigned_add(std::move(*this), std::move(other));

			m_is_negative = true;
		}
		else
		if (!m_is_negative &&  other.m_is_negative)
		{
			if (this->unsigned_less(other))
			{
				*this = unsigned_sub(std::move(other), std::move(*this));

				m_is_negative = true;
			}
			else
			{
				*this = unsigned_sub(std::move(*this), std::move(other));
			}
		}
		else
		if ( m_is_negative && !other.m_is_negative)
		{
			if (this->unsigned_less(other))
			{
				*this = unsigned_sub(std::move(other), std::move(*this));
			}
			else
			{
				*this = unsigned_sub(std::move(*this), std::move(other));

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

private:

	Big_Int unsigned_add(Big_Int && lhs, Big_Int && rhs) const
	{
		lhs.m_n_digits = std::max(lhs.m_n_digits, rhs.m_n_digits);

		for (std::size_t i = 0; i < lhs.m_n_digits; ++i)
		{
			lhs.m_digits[i] += rhs.m_digits[i];

			if (lhs.m_digits[i] >= Big_Int::base)
			{
				lhs.m_digits[i] -= Big_Int::base;

				if (i < lhs.size - 1)
				{
					++lhs.m_digits[i + 1];
				}
				else throw std::overflow_error("too many digits");
			}
		}

		lhs.m_n_digits += (lhs.m_digits[lhs.m_n_digits]);

		return lhs;
	}

	Big_Int unsigned_sub(Big_Int && lhs, Big_Int && rhs) const noexcept
	{
		lhs.m_is_negative = false;

		for (std::size_t i = 0; i < lhs.m_n_digits; ++i)
		{
			lhs.m_digits[i] -= rhs.m_digits[i];

			if (lhs.m_digits[i] < 0)
			{
				lhs.m_digits[i] += Big_Int::base;

				lhs.m_digits[i + 1]--;
			}
		}

		auto position = lhs.m_n_digits;

		while (position > 0 && !lhs.m_digits[position]) --position;

		lhs.m_n_digits = position + 1;

		return lhs;
	}

public:

	auto & operator++() { *this += 1; return *this; }
	auto & operator--() { *this -= 1; return *this; }

	const auto operator++(int)
	{
		Big_Int tmp(*this); ++(*this); return tmp;
	}

	const auto operator--(int)
	{
		Big_Int tmp(*this); --(*this); return tmp;
	}

public:

	[[nodiscard]] friend auto operator< (const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		if ( lhs.m_is_negative && !rhs.m_is_negative) return true;
		if (!lhs.m_is_negative &&  rhs.m_is_negative) return false;

		if (!lhs.m_is_negative && !rhs.m_is_negative) return lhs.unsigned_less(rhs);
		if ( lhs.m_is_negative &&  rhs.m_is_negative) return rhs.unsigned_less(lhs);
	}

	[[nodiscard]] friend auto operator> (const Big_Int & lhs, const Big_Int & rhs) noexcept
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

[[nodiscard]] inline const auto operator+(Big_Int lhs, Big_Int rhs)
{
	return (lhs += rhs);
}

[[nodiscard]] inline const auto operator-(Big_Int lhs, Big_Int rhs)
{
	return (lhs -= rhs);
}

/*
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
*/

int main()
{
	try
	{
		Big_Int bi1;
		Big_Int bi2(42);
		Big_Int bi3("123456789");

		Big_Int bi4; std::cin >> bi4;
		Big_Int bi5; std::cin >> bi5;

		std::cout << bi4 + bi5 << std::endl;
		std::cout << bi4 - bi5 << std::endl;

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