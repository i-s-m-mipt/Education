#include <type_traits>

/////////////////////////////////////////////////////////////////////////////////

template < typename T > class is_integral : public std::integral_constant 
< 
	bool, std::is_same_v < T, bool  > || 
	
          std::is_same_v < T, char  > || 

          std::is_same_v < T, short > ||

          std::is_same_v < T, int   > ||

          std::is_same_v < T, long  > 
> {};

/////////////////////////////////////////////////////////////////////////////////

template < typename T > constexpr auto is_integral_v = is_integral < T > ::value;

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert( is_integral_v < int    > );
		
	static_assert(!is_integral_v < double > );
}