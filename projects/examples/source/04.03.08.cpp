////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <utility>

////////////////////////////////////////////////////////////////////

template < typename ... Ts > class Tuple {};

////////////////////////////////////////////////////////////////////

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
	
	Tuple < Ts ... > m_tail;
};

////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(Tuple < int, double > (1, 1.0).get < 0 > () == 1);
}

////////////////////////////////////////////////////////////////////