#include <cstddef>
#include <type_traits>

// =================================================================================================

template < typename T1, typename T2 > struct is_same            : public std::false_type {};
template < typename T1              > struct is_same < T1, T1 > : public std:: true_type {};

template < typename T1, typename T2 > inline constexpr auto is_same_v = is_same < T1, T2 > ::value;

template < typename T1, typename ... Types > inline constexpr bool is_homogeneous(T1, Types...)
{
	return (is_same_v < T1, Types > && ...);
}

// =================================================================================================

template < typename T > struct remove_reference          { using type = T; };
template < typename T > struct remove_reference < T &  > { using type = T; };
template < typename T > struct remove_reference < T && > { using type = T; };

template < typename T > using  remove_reference_t = typename remove_reference < T > ::type;

// =================================================================================================

template < typename T > struct add_lvalue_reference { using type = T &  ; };
template < typename T > struct add_rvalue_reference { using type = T && ; };

template < typename T > using  add_lvalue_reference_t = typename add_lvalue_reference < T > ::type;
template < typename T > using  add_rvalue_reference_t = typename add_rvalue_reference < T > ::type;

// =================================================================================================

template < typename T > struct is_array         : public std::false_type {};

template < typename T > struct is_array < T[] > : public std:: true_type
{
	using type = T;

	static constexpr auto size = 0;

}; // template < typename T > struct is_array < T[] > : std::true_type

template < typename T, std::size_t N > struct is_array < T[N] > : public std::true_type
{
	using type = T;

	static constexpr auto size = N;

}; // template < typename T, std::size_t N > struct is_array < T[N] > : std::true_type

template < typename T > inline constexpr auto is_array_v = is_array < T > ::value;

// =================================================================================================

template < typename D, typename B > class is_derived
{
private:

	class N { std::byte data[1]; }; // note: sizeof(N) is 1
	class Y { std::byte data[2]; }; // note: sizeof(Y) is 2

private:

	static constexpr N test(...) {}; // note: C-style for inheritance
	static constexpr Y test(B *) {};

public:

	static constexpr auto value = (sizeof(test(static_cast < D * > (nullptr))) == sizeof(Y));

}; // template < typename D, typename B > class is_derived

template < typename D, typename B > inline constexpr auto is_derived_v = is_derived < D, B > ::value;

// =================================================================================================

class Base {}; class Derived : public Base {}; class Empty {};

// =================================================================================================

template < bool C, typename TT, typename FT > struct if_then_else                   { using type = TT; };
template <         typename TT, typename FT > struct if_then_else < false, TT, FT > { using type = FT; };

template < bool C, typename TT, typename FT > using  if_then_else_t = typename if_then_else < C, TT, FT > ::type;

// =================================================================================================

int main()
{
	static_assert( is_same_v < int, int    > );
	static_assert(!is_same_v < int, double > );

	static_assert( is_homogeneous('a', 'b', 'c'));
	static_assert(!is_homogeneous('a', 'b', 1.0));

	static_assert( is_same_v < remove_reference_t < int    > , int > );
	static_assert( is_same_v < remove_reference_t < int &  > , int > );
	static_assert( is_same_v < remove_reference_t < int && > , int > );

	static_assert( is_same_v < add_lvalue_reference_t < int > , int &  > );
	static_assert( is_same_v < add_rvalue_reference_t < int > , int && > );

	static_assert(!is_array_v < int    > );
	static_assert( is_array_v < int[ ] > );
	static_assert( is_array_v < int[5] > );

	static_assert( is_same_v < is_array < int[5] > ::type, int > );
	static_assert(             is_array < int[5] > ::size == 5   );

	static_assert( is_derived_v < Derived, Base > );
	static_assert(!is_derived_v <   Empty, Base > );

	return 0;
}