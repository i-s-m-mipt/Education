//////////////////////////////////////////////////////////////////

#include <cstddef>
#include <utility>

//////////////////////////////////////////////////////////////////

template < typename ... Ts > class Tuple {};

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public :

	constexpr Tuple(T && x, Ts && ... ys)
	:
		m_head(std::forward < T  > (x )   ), 
		
		m_tail(std::forward < Ts > (ys)...)
	{}

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

private :

	T m_head;

//  -----------------------------------------------------
	
	Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////

int main()
{
	constexpr Tuple < int, double > tuple(1, 1.0);

//  ----------------------------------------------

	static_assert(tuple.get < 0 > () == 1);
}

//////////////////////////////////////////////////////////////////