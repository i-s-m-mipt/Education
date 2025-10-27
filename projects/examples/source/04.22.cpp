//////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

//////////////////////////////////////////////////////////////////

template < typename ... Ts > class Tuple {};

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public :

	Tuple(T && x, Ts && ... ys)
	:
		m_head(std::forward < T  > (x )   ),
		
		m_tail(std::forward < Ts > (ys)...)
	{}

//  ------------------------------------------------

	template < std::size_t I > auto get() const
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
	
	Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////

int main()
{
	Tuple < int, double, std::string > tuple(1, 2.0, "aaaaa");

//  ----------------------------------------------------------

	assert(tuple.get < 0 > () == 1);
}

//////////////////////////////////////////////////////////////////