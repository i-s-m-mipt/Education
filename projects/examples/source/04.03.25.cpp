//////////////////////////////////////////////////////////////////

#include <cstddef>
#include <string>
#include <utility>

//////////////////////////////////////////////////////////////////

template < typename ... Ts > class Tuple {};

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public :

	constexpr Tuple() = default;

//  ------------------------------------------------------

	constexpr Tuple(T && x, Ts && ... ys)
	:
		m_head(std::forward < T  > (x )   ), 
		
		m_tail(std::forward < Ts > (ys)...)
	{}

//  ------------------------------------------------------

	constexpr Tuple            (const Tuple & ) = default;

	constexpr Tuple            (      Tuple &&) = default;

//  ------------------------------------------------------

	constexpr Tuple & operator=(const Tuple & ) = default;

	constexpr Tuple & operator=(      Tuple &&) = default;

//  ------------------------------------------------------

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

private :

	T m_head;

//  ------------------------------------------------------
	
	Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////

int main()
{
    Tuple < int, std::string > tuple_1;

	Tuple < int, std::string > tuple_2(2, "aaaaa");

//  --------------------------------------------------------

	Tuple < int, std::string > tuple_3 = tuple_2;

							   tuple_3 = tuple_2;

//  --------------------------------------------------------

    Tuple < int, std::string > tuple_4 = std::move(tuple_3);
    
    						   tuple_4 = std::move(tuple_3);

//  --------------------------------------------------------

	constexpr Tuple < int, char * > tuple_5(1, "aaaaa");

//  --------------------------------------------------------

	static_assert(tuple_5.get < 0 > () == 1);
}

//////////////////////////////////////////////////////////////////