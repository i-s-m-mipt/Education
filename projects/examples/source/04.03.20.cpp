#include <type_traits>

//////////////////////////////////////////////////////////////////////////////////////////

template < bool C, typename T > struct enable_if {};

template <         typename T > struct enable_if < true, T > 
{ 
	using type = T;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < bool C, typename T > using enable_if_t = typename enable_if < C, T > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(std::is_same_v <      enable_if_t < true , int > , int > == 1);

//	static_assert(std::is_same_v <      enable_if_t < false, int > , int > == 0); // error

//  --------------------------------------------------------------------------------------

	static_assert(std::is_same_v < std::enable_if_t < true , int > , int > == 1);

//	static_assert(std::is_same_v < std::enable_if_t < false, int > , int > == 0); // error
}