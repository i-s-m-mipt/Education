#include <cstddef>
#include <string>
#include <utility>

////////////////////////////////////////////////////////////////////

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

//  ------------------------------------------------------------

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

////////////////////////////////////////////////////////////////////

template < typename ... Ts > constexpr auto make_tuple(Ts && ... xs)
{
	return Tuple < Ts ... > (std::forward < Ts > (xs)...);
}

////////////////////////////////////////////////////////////////////

int main()
{
    Tuple < int, std::string > tuple_1;

	Tuple < int, std::string > tuple_2(2, "bbbbb");

//  -------------------------------------------------------

	Tuple < int, std::string > tuple_3(tuple_2);

    Tuple < int, std::string > tuple_4(std::move(tuple_3));

//  -------------------------------------------------------

    tuple_3 = tuple_2;
    
    tuple_4 = std::move(tuple_3);

//  -------------------------------------------------------

	static_assert(make_tuple(1, 2, 3).get < 0 > () == 1);
}