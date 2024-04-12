#include <compare>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <utility>

// =================================================================================================

template <             typename ... Ts > class Tuple;
template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public:

	constexpr Tuple() = default;

	constexpr explicit Tuple(T && head, Ts && ... tail) : // note: conditionally explicit in std
		m_head(std::forward < T  > (head)   ), 
		m_tail(std::forward < Ts > (tail)...) {}

	constexpr Tuple(const Tuple &  other) : m_head(          other.m_head ), m_tail(          other.m_tail ) {}
	constexpr Tuple(      Tuple && other) : m_head(std::move(other.m_head)), m_tail(std::move(other.m_tail)) {}

	constexpr Tuple & operator=(Tuple other) { swap(other); return *this; } // good: copy and swap idiom

public:

	[[nodiscard]] constexpr const         T        & head() const { return m_head; }
	[[nodiscard]] constexpr               T        & head()       { return m_head; }

	[[nodiscard]] constexpr const Tuple < Ts ... > & tail() const { return m_tail; }
	[[nodiscard]] constexpr       Tuple < Ts ... > & tail()       { return m_tail; }

public:

	constexpr void swap(Tuple & other) 
	{
		using std::swap; // good: enable argument-dependent lookup

		if constexpr (swap(m_head, other.m_head); sizeof...(Ts) > 0) { m_tail.swap(other.m_tail); }
	}

private:

	T m_head; Tuple < Ts ... > m_tail;

}; // template < typename T, typename ... Ts > class Tuple < T, Ts ... >

template <> class Tuple <> {};

// =================================================================================================

template < typename ... Ts > inline constexpr void swap(Tuple < Ts ... > & x, Tuple < Ts ... > & y)
{
	if constexpr (sizeof...(Ts) > 0) { x.swap(y); }
}

// =================================================================================================

template < std::size_t N > struct Get
{
	template < typename T, typename ... Ts > requires (N < sizeof...(Ts) + 1)
	[[nodiscard]] static constexpr const auto & apply(const Tuple < T, Ts ...> & tuple)
	{
		return Get < N - 1 > ::apply(tuple.tail());
	}

	template < typename T, typename ... Ts > requires (N < sizeof...(Ts) + 1)
	[[nodiscard]] static constexpr auto & apply(Tuple < T, Ts ...> & tuple)
	{
		return Get < N - 1 > ::apply(tuple.tail());
	}

}; // template < std::size_t N > struct Get

template <> struct Get < 0 >
{
	template < typename T, typename ... Ts >
	[[nodiscard]] static constexpr const auto & apply(const Tuple < T, Ts ... > & tuple)
	{
		return tuple.head();
	}

	template < typename T, typename ... Ts >
	[[nodiscard]] static constexpr auto & apply(Tuple < T, Ts ... > & tuple)
	{
		return tuple.head();
	}

}; // template <> struct Get < 0 >

template < std::size_t N, typename ... Ts > requires (N < sizeof...(Ts))
[[nodiscard]] inline constexpr const auto & get(const Tuple < Ts ... > & tuple)
{
	return Get < N > ::apply(tuple);
}

template < std::size_t N, typename ... Ts > requires (N < sizeof...(Ts))
[[nodiscard]] inline constexpr auto & get(Tuple < Ts ... > & tuple)
{
	return Get < N > ::apply(tuple);
}

// =================================================================================================

template < typename ... Ts > [[nodiscard]] inline constexpr auto make_tuple(Ts && ... elements)
{
	return Tuple < std::decay_t < Ts > ... > (std::forward < Ts > (elements)...);
}

// =================================================================================================

[[nodiscard]] inline constexpr bool operator==(const Tuple <> &, const Tuple <> &)
{
	return true;
}

template < typename ... Ts, 
		   typename ... Us > requires (sizeof...(Ts) == sizeof...(Us))
[[nodiscard]] inline constexpr bool operator==(
	const Tuple < Ts ... > & lhs, 
	const Tuple < Us ... > & rhs)
{
	return ((lhs.head() == rhs.head()) && (lhs.tail() == rhs.tail()));
}

// =================================================================================================

[[nodiscard]] inline constexpr std::strong_ordering operator<=>(const Tuple <> &, const Tuple <> &)
{
	return std::strong_ordering::equivalent;
}

template < typename ... Ts, 
		   typename ... Us > requires (sizeof...(Ts) == sizeof...(Us))
[[nodiscard]] inline constexpr std::strong_ordering operator<=>(
	const Tuple < Ts ... > & lhs, 
	const Tuple < Us ... > & rhs)
{
	if (lhs.head() == rhs.head())
	{
		return lhs.tail() <=> rhs.tail();
	}
	else
	{
		return (lhs.head() < rhs.head() ? std::strong_ordering::less : std::strong_ordering::greater);
	}
}

// =================================================================================================

inline void print(std::ostream & stream, const Tuple <> &, bool is_first = true)
{
	stream << (is_first ? "{}" : " }");
}

template < typename T, typename ... Ts > 
inline void print(std::ostream & stream, const Tuple < T, Ts ... > & tuple, bool is_first = true)
{
	stream << (is_first ? "{ " : ", ") << tuple.head();

	print(stream, tuple.tail(), false);
}

template < typename ... Ts > 
inline std::ostream & operator<<(std::ostream & stream, const Tuple < Ts ... > & tuple)
{
	print(stream, tuple); return stream;
}

// =================================================================================================

int main()
{
	constexpr auto tuple_1 = make_tuple('a', 42, 3.14);

	std::cout << tuple_1 << std::endl;

	std::cout << make_tuple() << std::endl;

	static_assert(get < 0 > (tuple_1) ==  'a');
	static_assert(get < 1 > (tuple_1) ==   42);
	static_assert(get < 2 > (tuple_1) == 3.14);

	auto tuple_2 = make_tuple('a', 42, 2.72);

	get < 2 > (tuple_2) = get < 2 > (tuple_1);

	std::cout << "tuple_1 <  tuple_2: " << (tuple_1 <  tuple_2) << std::endl;
    std::cout << "tuple_1 >  tuple_2: " << (tuple_1 >  tuple_2) << std::endl;
    std::cout << "tuple_1 <= tuple_2: " << (tuple_1 <= tuple_2) << std::endl;
    std::cout << "tuple_1 >= tuple_2: " << (tuple_1 >= tuple_2) << std::endl;
    std::cout << "tuple_1 == tuple_2: " << (tuple_1 == tuple_2) << std::endl;
    std::cout << "tuple_1 != tuple_2: " << (tuple_1 != tuple_2) << std::endl;

	return 0;
}