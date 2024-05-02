#include <cctype>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

using namespace std::literals;

#include <gtest/gtest.h>

//  ================================================================================================

class Big_Int
{
public:

	using digit_t = long long; // note: 8 byte(s) at least

public:

	Big_Int() : m_is_negative(false), m_n_digits(1), m_digits(size, 0) {}

	Big_Int(digit_t number) : Big_Int() { parse(std::to_string(number)); }

	Big_Int(std::string_view string) : Big_Int() { parse(string); }

private:

	void parse(std::string_view string)
	{
		if (string[0] == '+' || string[0] == '-' || std::isdigit(string[0]))
		{
			if (!std::isdigit(string[0]) && std::size(string) == 1)
			{
				throw std::invalid_argument("invalid input: "s + string[0]);
			}

			for (std::size_t i = 1; i < std::size(string); ++i)
			{
				if (!std::isdigit(string[i]))
				{
					throw std::invalid_argument("invalid input: "s + string[i]);
				}
			}

			m_is_negative = (string[0] == '-'); m_n_digits = 0;

			for (auto i = static_cast < int > (std::size(string)) - 1; i >= 0; i -= step)
			{
				auto start = i - step + 1;

				if (start <= 0) start = (m_is_negative ? 1 : 0);

				m_digits[m_n_digits++] = std::stoll(static_cast < std::string > (string.substr(start, i - start + 1)));
			}

			reduce_leading_zeros();
		}
		else throw std::invalid_argument("invalid input: "s + string[0]);
	}

	void reduce_leading_zeros() noexcept
	{
		for (; m_n_digits > 1 && !m_digits[m_n_digits - 1]; --m_n_digits);
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

	Big_Int & operator+=(Big_Int other)
	{
		if ((!m_is_negative && !other.m_is_negative) ||
			( m_is_negative &&  other.m_is_negative))
		{
			this->unsigned_add(other);
		}
		else if (!m_is_negative &&  other.m_is_negative)
		{
			if (this->unsigned_less(other))
			{
				*this = std::move(other.unsigned_sub(*this)); 
				
				m_is_negative = true;
			}
			else this->unsigned_sub(other);
		}
		else if ( m_is_negative && !other.m_is_negative)
		{
			if (this->unsigned_less(other))
			{
				*this = std::move(other.unsigned_sub(*this));
			}
			else { this->unsigned_sub(other); m_is_negative = true; }
		}

		return *this;
	}

	Big_Int & operator-=(Big_Int other)
	{
		other.m_is_negative = !other.m_is_negative;

		return (*this += other);
	}

	Big_Int & operator*=(Big_Int other)
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

				r = result.m_digits[i + j] / Big_Int::radix;

				result.m_digits[i + j] -= (r * Big_Int::radix);
			}
		}

		result.m_n_digits = m_n_digits + other.m_n_digits;

		swap(result); reduce_leading_zeros(); return *this;
	}

	Big_Int & operator/=(Big_Int other)
	{
		if (other.m_n_digits == 0 || (other.m_n_digits == 1 && other.m_digits.front() == 0))
		{
			throw std::domain_error("division by zero");
		}

		Big_Int result; result.m_n_digits = m_n_digits;

		result.m_is_negative = m_is_negative ^ other.m_is_negative; other.m_is_negative = false;

		Big_Int current;

		for (auto i = static_cast < int > (m_n_digits) - 1; i >= 0; --i)
		{
			current *= Big_Int::radix; current.m_digits[0] = m_digits[i];

			digit_t l = 0, r = Big_Int::radix, v = 0;

			while (l <= r)
			{
				if (auto m = std::midpoint(l, r); other * m <= current)
				{
					l = m + 1; v = m;
				}
				else
				{
					r = m - 1;
				}
			}

			result.m_digits[i] = v; current -= other * v;
		}

		swap(result); reduce_leading_zeros(); return *this;
	}

private:

	Big_Int & unsigned_add(const Big_Int & other)
	{
		m_n_digits = std::max(m_n_digits, other.m_n_digits);

		for (std::size_t i = 0; i < m_n_digits; ++i)
		{
			if (m_digits[i] += other.m_digits[i]; m_digits[i] >= Big_Int::radix)
			{
				if (m_digits[i] -= Big_Int::radix; i < size - 1)
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
				m_digits[i] += Big_Int::radix;

				m_digits[i + 1]--;
			}
		}

		reduce_leading_zeros(); return *this;
	}

public:

	Big_Int & operator++() 
	{ 
		*this += 1; return *this; 
	}

	Big_Int & operator--() 
	{ 
		*this -= 1; return *this; 
	}

	const Big_Int operator++(int)
	{
		Big_Int t(*this); ++(*this); return t;
	}

	const Big_Int operator--(int)
	{
		Big_Int t(*this); --(*this); return t;
	}

public:

	[[nodiscard]] friend Big_Int karatsuba_multiplication(const Big_Int & x, const Big_Int & y)
	{
		auto n = std::max(x.m_n_digits, y.m_n_digits);

		if (n == 1) return x * y;

		auto k = n / 2;

		Big_Int xr; xr.m_n_digits =     k; // note: slow memory allocation
		Big_Int xl; xl.m_n_digits = n - k; // note: slow memory allocation

		for (std::size_t i =     0; i < k; ++i) xr.m_digits[i    ] = x.m_digits[i];
		for (std::size_t i = n / 2; i < n; ++i) xl.m_digits[i - k] = x.m_digits[i];

		Big_Int yr; yr.m_n_digits =     k; // note: slow memory allocation
		Big_Int yl; yl.m_n_digits = n - k; // note: slow memory allocation

		for (std::size_t i = 0; i < n / 2; ++i) yr.m_digits[i    ] = y.m_digits[i];
		for (std::size_t i = k; i < n    ; ++i) yl.m_digits[i - k] = y.m_digits[i];

		auto p1 = karatsuba_multiplication(xl,      yl     );
		auto p2 = karatsuba_multiplication(xr,      yr     );
		auto p3 = karatsuba_multiplication(xl + xr, yl + yr);

		Big_Int radix = Big_Int::radix; // note: slow memory allocation

		for (std::size_t i = 1; i < n / 2; ++i) radix *= Big_Int::radix;

		auto result = (p1 * radix * radix + (p3 - p2 - p1) * radix + p2);

		result.m_is_negative = x.m_is_negative ^ y.m_is_negative; 

		return result;
	}

	[[nodiscard]] friend Big_Int sqrt(const Big_Int & x)
	{
		if (x.m_is_negative) throw std::domain_error("invalid argument");

		auto position = (static_cast < int > (x.m_n_digits) + 1) / 2;

    	Big_Int result; result.m_n_digits = position;
    	
    	for (--position; position >= 0; --position)
    	{
      		digit_t l = 0, r = Big_Int::radix, v = 0;

      		while (l <= r)
      		{
        		if (auto m = result.m_digits[position] = std::midpoint(l, r); result * result <= x)
        		{
          			l = m + 1; v = m;
        		}
        		else
				{
					r = m - 1;
				}				
      		}

      		result.m_digits[position] = v;
    	}

		result.reduce_leading_zeros(); return result; 
	}

public:

	[[nodiscard]] friend Big_Int operator+(Big_Int lhs, Big_Int rhs) { return (lhs += rhs); }
	[[nodiscard]] friend Big_Int operator-(Big_Int lhs, Big_Int rhs) { return (lhs -= rhs); }
	[[nodiscard]] friend Big_Int operator*(Big_Int lhs, Big_Int rhs) { return (lhs *= rhs); }
	[[nodiscard]] friend Big_Int operator/(Big_Int lhs, Big_Int rhs) { return (lhs /= rhs); }

public:

	[[nodiscard]] friend bool operator< (const Big_Int & lhs, const Big_Int & rhs) noexcept
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

	[[nodiscard]] friend bool operator> (const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return (rhs < lhs);
	}

	[[nodiscard]] friend bool operator<=(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return !(rhs < lhs);
	}

	[[nodiscard]] friend bool operator>=(const Big_Int & lhs, const Big_Int & rhs) noexcept
	{
		return !(lhs < rhs);
	}

	[[nodiscard]] friend bool operator==(const Big_Int & lhs, const Big_Int & rhs) noexcept
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

	static constexpr auto step = std::numeric_limits < digit_t > ::digits10 / 2;

	static constexpr auto radix = static_cast < digit_t > (std::pow(10, step));

public:

	static constexpr std::size_t size = 1'000; // note: maximum number of digits

private:

	bool m_is_negative;

	std::size_t m_n_digits;

	std::vector < digit_t > m_digits; 

}; // class Big_Int

//  ================================================================================================

inline void swap(Big_Int & x, Big_Int & y) noexcept { x.swap(y); }

//  ================================================================================================

TEST(Big_Int, Operators)
{
	const Big_Int big_int_1 = "+73640854127382725310948206095647"sv;
	const Big_Int big_int_2 = "-46090058756232818791046807807190"sv;

//  ================================================================================================

    ASSERT_EQ(big_int_1 + big_int_1, "+147281708254765450621896412191294"sv);
	ASSERT_EQ(big_int_1 + big_int_2,  "+27550795371149906519901398288457"sv);
	ASSERT_EQ(big_int_2 + big_int_1,  "+27550795371149906519901398288457"sv);
	ASSERT_EQ(big_int_2 + big_int_2,  "-92180117512465637582093615614380"sv);

	ASSERT_EQ(big_int_1 - big_int_1,                                 "+0"sv);
	ASSERT_EQ(big_int_1 - big_int_2, "+119730912883615544101995013902837"sv);
	ASSERT_EQ(big_int_2 - big_int_1, "-119730912883615544101995013902837"sv);
	ASSERT_EQ(big_int_2 - big_int_2,                                 "-0"sv);

	ASSERT_EQ(big_int_1 * big_int_1, "+5422975396610461369717641600947386274415037870250962127712348609"sv);
	ASSERT_EQ(big_int_1 * big_int_2, "-3394111293590239892710602762023649092547630961329778427474301930"sv);
	ASSERT_EQ(big_int_2 * big_int_1, "-3394111293590239892710602762023649092547630961329778427474301930"sv);
	ASSERT_EQ(big_int_2 * big_int_2, "+2124293516152993531053750721748717735666440864785393936215696100"sv);

	ASSERT_EQ(big_int_1 / big_int_1, "+1"sv);
	ASSERT_EQ(big_int_1 / big_int_2, "-1"sv);
	ASSERT_EQ(big_int_2 / big_int_1, "-0"sv);
	ASSERT_EQ(big_int_2 / big_int_2, "+1"sv);

//  ================================================================================================

	Big_Int big_int_3 = 42;

	ASSERT_EQ(++big_int_3  , 43); 
	ASSERT_EQ(--big_int_3  , 42);
	ASSERT_EQ(  big_int_3++, 42); 
	ASSERT_EQ(  big_int_3--, 43);

//  ================================================================================================

	ASSERT_EQ(sqrt(big_int_1), "+8581424947372244"sv);
}

//  ================================================================================================

TEST(Big_Int, Karatsuba_Multiplication)
{
	const Big_Int big_int_1 = "+73640854127382725310948206095647"sv;
	const Big_Int big_int_2 = "-46090058756232818791046807807190"sv;

//  ================================================================================================

	ASSERT_EQ(karatsuba_multiplication(big_int_1, big_int_1), "+5422975396610461369717641600947386274415037870250962127712348609"sv);
	ASSERT_EQ(karatsuba_multiplication(big_int_1, big_int_2), "-3394111293590239892710602762023649092547630961329778427474301930"sv);
	ASSERT_EQ(karatsuba_multiplication(big_int_2, big_int_1), "-3394111293590239892710602762023649092547630961329778427474301930"sv);
	ASSERT_EQ(karatsuba_multiplication(big_int_2, big_int_2), "+2124293516152993531053750721748717735666440864785393936215696100"sv);
}

//  ================================================================================================

TEST(Big_Int, Comparisons)
{
	const Big_Int big_int_1 = "+73640854127382725310948206095647"sv;
	const Big_Int big_int_2 = "-46090058756232818791046807807190"sv;

//  ================================================================================================

	ASSERT_TRUE(big_int_2 <  big_int_1);
	ASSERT_TRUE(big_int_1 >  big_int_2);
	ASSERT_TRUE(big_int_2 <= big_int_1);
	ASSERT_TRUE(big_int_1 >= big_int_2);
	ASSERT_TRUE(big_int_1 != big_int_2);
}

//  ================================================================================================

int main(int argc, char ** argv) // note: arguments for testing
{
	try
	{
		Big_Int big_int{}; std::cin >> big_int; std::cout << big_int << std::endl;

		Big_Int result(1); for (auto i = 1; i < 101; ++i) result *= i;

		std::cout << result << std::endl; // note: outputs 100!
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

//  ================================================================================================

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}