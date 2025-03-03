#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////

template < bool C, typename T > struct enable_if {};

template <         typename T > struct enable_if < 1, T > 
{ 
	using type = T;
};

///////////////////////////////////////////////////////////////////////////////////////

template < bool C, typename T > using enable_if_t = typename enable_if < C, T > ::type;

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert( std::is_same_v < enable_if_t < 1 + 2 == 3, int > , int > );

//	static_assert(!std::is_same_v < enable_if_t < 1 + 2 != 3, int > , int > ); // error
}