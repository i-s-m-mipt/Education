#include <cassert>
#include <compare>
#include <iostream>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::literals;

//  ================================================================================================

template <             typename ... Ts > class Tuple {};

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public:

	constexpr Tuple() = default;

	constexpr Tuple(T && head, Ts && ... tail) 
	:
		m_head(std::forward < T  > (head)   ), 
		m_tail(std::forward < Ts > (tail)...) 
	{}

	constexpr Tuple(const Tuple &  other) 
	: 
		m_head(other.m_head), 
		m_tail(other.m_tail) 
	{}

	constexpr Tuple(Tuple && other) 
	: 
		m_head(std::move(other.m_head)), 
		m_tail(std::move(other.m_tail)) 
	{}

	constexpr auto & operator=(Tuple other) 
	{ 
		swap(other); 
		
		return *this; 
	}

//  ------------------------------------------------------------------------------------------------

	constexpr void swap(Tuple & other) const
	{
		using std::swap; 

		swap(m_head, other.m_head);

		if constexpr (sizeof...(Ts) > 0) 
		{ 
			m_tail.swap(other.m_tail); 
		}
	}

//  --------------------------------------------------------------------

	constexpr const auto & head() const { return m_head; }
	constexpr       auto & head()       { return m_head; }

	constexpr const auto & tail() const { return m_tail; }
	constexpr       auto & tail()       { return m_tail; }

private:

	T m_head; Tuple < Ts ... > m_tail;
};

//  ================================================================================================

template < typename ... Ts > constexpr auto make_tuple(Ts && ... args)
{
	return Tuple < Ts ... > (std::forward < Ts > (args)...);
}

//  ================================================================================================

template < std::size_t I > struct Get 
{
	template < typename T, typename ... Ts > static constexpr const auto & apply
	(
		const Tuple < T, Ts ...> & tuple
	)
	{
		return Get < I - 1 > ::apply(tuple.tail());
	}

	template < typename T, typename ... Ts > static constexpr auto & apply
	(
		Tuple < T, Ts ...> & tuple
	)
	{
		return Get < I - 1 > ::apply(tuple.tail());
	}
};

//  ================================================================================================

template <> struct Get < 0 >
{
	template < typename T, typename ... Ts > static constexpr const auto & apply
	(
		const Tuple < T, Ts ... > & tuple
	)
	{
		return tuple.head();
	}

	template < typename T, typename ... Ts > static constexpr auto & apply
	(
		Tuple < T, Ts ... > & tuple
	)
	{
		return tuple.head();
	}
};

//  ================================================================================================

template 
< 
	std::size_t I, typename ... Ts 
> 
constexpr const auto & get(const Tuple < Ts ... > & tuple)
{
	return Get < I > ::apply(tuple);
}

template < std::size_t I, typename ... Ts > constexpr auto & get(Tuple < Ts ... > & tuple)
{
	return Get < I > ::apply(tuple);
}

//  ================================================================================================

constexpr auto operator==(const Tuple <> & , const Tuple <> &)
{
	return true;
}

template 
< 
	typename ... Ts, 
	typename ... Us 
> 
constexpr auto operator==
(
	const Tuple < Ts ... > & lhs, 
	const Tuple < Us ... > & rhs
)
{
	return lhs.head() == rhs.head() && lhs.tail() == rhs.tail();
}

//  ================================================================================================

constexpr auto operator<=>(const Tuple <> & , const Tuple <> &)
{
	return std::strong_ordering::equivalent;
}

template 
< 
	typename ... Ts, 
	typename ... Us 
> 
constexpr auto operator<=>
(
	const Tuple < Ts ... > & lhs, 
	const Tuple < Us ... > & rhs
)
{
	if (lhs.head() == rhs.head())
	{
		return lhs.tail() <=> rhs.tail();
	}
	else
	{
		if (lhs.head() < rhs.head())
		{
			return std::strong_ordering::less;
		}
		else
		{
			return std::strong_ordering::greater;
		}
	}
}

//  ================================================================================================

template < typename T, std::size_t I > struct Helper
{
    static void print(std::ostream & stream, const T & tuple)
    {
        Helper < T, I - 1 > ::print(stream, tuple);

        stream << " " << get < I - 1 > (tuple);
    }
};
    
template < typename T > struct Helper < T, 1 >
{
    static void print(std::ostream & stream, const T & tuple)
    {
        stream << get < 0 > (tuple);
    }
};

//  ================================================================================================

template 
< 
    typename ... Ts 
> 
auto & operator<<(std::ostream & stream, const Tuple < Ts ... > & tuple)
{
    if constexpr (sizeof...(Ts) > 0)
    {
        stream << "{ ";

        Helper < decltype(tuple), sizeof...(Ts) > ::print(stream, tuple);

        stream << " }";
    }
	else
    {
        stream << "{}";
    }
    
    return stream;
}

//  ================================================================================================

int main()
{
	constexpr auto tuple_c = make_tuple('a', 1, 1.0);

//  -------------------------------------------------

	static_assert(get < 1 > (tuple_c) == 1);

//  -----------------------------------------

	auto tuple_1 = ::make_tuple(1, "aaaaa"s);
	
	auto tuple_2 = tuple_1;

//  ------------------------

	get < 0 > (tuple_2) = 2;

	get < 1 > (tuple_2) = "bbbbb"s;

//  -------------------------------

	auto f = false, t = true;

//  ----------------------------------

	assert((tuple_1 <  tuple_2) == t);
    assert((tuple_1 >  tuple_2) == f);
    assert((tuple_1 <= tuple_2) == t);
    assert((tuple_1 >= tuple_2) == f);
    assert((tuple_1 == tuple_2) == f);
    assert((tuple_1 != tuple_2) == t);

//  ---------------------------------------------

	std::cout << "tuple_1 = " << tuple_1 << '\n';
	std::cout << "tuple_2 = " << tuple_2 << '\n';
}