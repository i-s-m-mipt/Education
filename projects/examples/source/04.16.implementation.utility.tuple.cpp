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

	constexpr Tuple(const Tuple & other) 
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

//  ----------------------------------------

	constexpr void swap(Tuple & other) const
	{
		using std::swap; 

		swap(m_head, other.m_head);

		if constexpr (sizeof...(Ts) > 0) 
		{ 
			m_tail.swap(other.m_tail); 
		}
	}

//  -----------------------------------------------------

	template < std::size_t I > constexpr auto get() const
	{
		if constexpr (I > 0)
		{
			return m_tail.template get < I - 1 > ();
		}
		else
		{
			return m_head;
		}
	}

private:

	T m_head; Tuple < Ts ... > m_tail;
};

//  ================================================================================================

template < typename ... Ts > constexpr auto make_tuple(Ts && ... args)
{
	return Tuple < Ts ... > (std::forward < Ts > (args)...);
}

//  ================================================================================================

template < typename T, std::size_t I > struct Helper
{
    static void print(std::ostream & stream, const T & tuple)
    {
        Helper < T, I - 1 > ::print(stream, tuple);

        stream << " " << tuple.template get < I - 1 > ();
    }
};
    
template < typename T > struct Helper < T, 1 >
{
    static void print(std::ostream & stream, const T & tuple)
    {
        stream << tuple.template get < 0 > ();
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
	Tuple < int, int, int > tuple_1;

	Tuple < int, int, int > tuple_2(1, 2, 3);

//  -----------------------------------------

	Tuple < int, int, int > tuple_3(tuple_2);

    Tuple < int, int, int > tuple_4(std::move(tuple_3));

    tuple_3 = tuple_2; 
    
    tuple_4 = std::move(tuple_3);

//  ----------------------------------

	assert(tuple_4.get < 0 > () == 1);

//  ---------------------------------------------

	std::cout << "tuple_4 = " << tuple_4 << '\n';

//  -----------------------------------------------

	constexpr auto tuple_5 = ::make_tuple(1, 2, 3);	
}