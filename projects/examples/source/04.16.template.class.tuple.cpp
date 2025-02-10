#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

using namespace std::literals;

//////////////////////////////////////////////////////////////////////

template <             typename ... Ts > class Tuple {};

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public:

	constexpr Tuple() = default;

	constexpr Tuple(T && x, Ts && ... xs)
	:
		m_head(std::forward < T  > (x )   ), 
		
		m_tail(std::forward < Ts > (xs)...)
	{}

	constexpr Tuple            (const Tuple &  other) = default;

	constexpr Tuple            (      Tuple && other) = default;

	constexpr Tuple & operator=(const Tuple &  other) = default;

	constexpr Tuple & operator=(      Tuple && other) = default;

//  ------------------------------------------------------------

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

	T m_head; 
	
	Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////////

template < typename ... Ts > constexpr auto make_tuple(Ts && ... xs)
{
	return Tuple < Ts ... > (std::forward < Ts > (xs)...);
}

//////////////////////////////////////////////////////////////////////

int main()
{
	{
		Tuple < int, std::string > tuple_1;

		Tuple < int, std::string > tuple_2(2, "bbbbb");

		Tuple < int, std::string > tuple_3(tuple_2);

    	Tuple < int, std::string > tuple_4(std::move(tuple_3));

    	tuple_3 = tuple_2;
    
    	tuple_4 = std::move(tuple_3);
	}

//  ------------------------------------------------------------------

	{
		static_assert(make_tuple(1, 2, 3).get < 0 > () == 1);
	}

//  ------------------------------------------------------------------

	{
        static_assert(std::get < 0 > (std::make_tuple(1, 2, 3)) == 1);
    }

//  ------------------------------------------------------------------

    {
        auto tuple = std::make_tuple(1, "aaaaa"s);

		static_assert(std::tuple_size_v < decltype(tuple) > == 2);

        auto x = 0;
        
        std::tie(x, std::ignore) = tuple;
        
        assert(x == 1);

        const auto & [y, string] = tuple; // support: cppinsights.io

        assert(y == 1 && string == "aaaaa");

        assert(std::tuple_cat(tuple, std::tuple <> ()) == tuple);
    }
}