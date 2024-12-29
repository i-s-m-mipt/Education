#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

////////////////////////////////////////////////////////////////////////

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

//  --------------------------------------------------------------------

	constexpr void swap(Tuple & other)
	{
		std::swap(m_head, other.m_head);

		if constexpr (sizeof...(Ts) > 0) 
		{ 
			m_tail.swap(other.m_tail); 
		}
	}

//  --------------------------------------------------------------------

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

//  --------------------------------------------------------------------

	friend auto & operator>>(std::istream & stream, Tuple & tuple)
	{
		stream >> tuple.m_head;

		if constexpr (sizeof...(Ts) > 0)
		{ 
			stream >> tuple.m_tail;
		}

		return stream;
	}

	friend auto & operator<<(std::ostream & stream, const Tuple & tuple)
	{
		stream << "{ "; tuple.write(stream); return stream << '}';
	}

//  --------------------------------------------------------------------

	void write(std::ostream & stream) const
	{
		stream << m_head << ' ';

		if constexpr (sizeof...(Ts) > 0)
		{
			m_tail.write(stream);
		}
	}

private:

	T m_head; Tuple < Ts ... > m_tail;
};

////////////////////////////////////////////////////////////////////////

template < typename ... Ts > constexpr auto make_tuple(Ts && ... args)
{
	return Tuple < Ts ... > (std::forward < Ts > (args)...);
}

////////////////////////////////////////////////////////////////////////

int main()
{
	[[maybe_unused]] Tuple < int, std::string > tuple_1;

	[[maybe_unused]] Tuple < int, std::string > tuple_2(1, "aaaaa");

//  ----------------------------------------------------------------

	Tuple < int, std::string > tuple_3(tuple_2);

    Tuple < int, std::string > tuple_4(std::move(tuple_3));

    tuple_3 = tuple_2; 
    
    tuple_4 = std::move(tuple_3);

//  ----------------------------------------------------------------

	assert(tuple_4.get < 0 > () == 1);

//  ----------------------------------------------------------------

	std::cout << "main : enter Tuple < int, std::string > : "; 
	
	Tuple < int, std::string > tuple_5; std::cin >> tuple_5; 
	
	std::cout << "main : tuple_5 = " << tuple_5 << '\n';

//  ----------------------------------------------------------------

	[[maybe_unused]] constexpr auto tuple_6 = make_tuple(1, 2, 3);	
}