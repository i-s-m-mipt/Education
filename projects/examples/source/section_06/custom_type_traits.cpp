#include <cstddef>
#include <type_traits>

// =================================================================================================

template < typename T1, typename T2 > struct is_same            : public std::false_type {};
template < typename T1              > struct is_same < T1, T1 > : public std:: true_type {};

template < typename T1, typename T2     > inline constexpr auto is_same_v = is_same < T1, T2 > ::value;

template < typename T1, typename ... Ts > inline constexpr auto is_homogeneous_v = (is_same_v < T1, Ts > && ...);

// =================================================================================================

template < typename T > struct  is_lvalue_reference          : std::false_type {};
template < typename T > struct  is_lvalue_reference < T & >  : std:: true_type {};

template < typename T > inline constexpr auto is_lvalue_reference_v = is_lvalue_reference < T > ::value;

template < typename T > struct  is_rvalue_reference          : std::false_type {};
template < typename T > struct  is_rvalue_reference < T && > : std:: true_type {};

template < typename T > inline constexpr auto is_rvalue_reference_v = is_rvalue_reference < T > ::value;

// =================================================================================================

template < typename T > struct     remove_reference          { using type = T    ; };
template < typename T > struct     remove_reference < T &  > { using type = T    ; };
template < typename T > struct     remove_reference < T && > { using type = T    ; };

template < typename T > using      remove_reference_t = typename remove_reference < T > ::type;

// =================================================================================================

template < typename T > struct add_lvalue_reference          { using type = T &  ; };
template < typename T > struct add_rvalue_reference          { using type = T && ; };

template < typename T > using  add_lvalue_reference_t = typename add_lvalue_reference < T > ::type;
template < typename T > using  add_rvalue_reference_t = typename add_rvalue_reference < T > ::type;

// =================================================================================================

template < typename T > struct is_integral : std::integral_constant < bool,
    is_same_v < bool  , remove_reference_t < T > > || 
	is_same_v < char  , remove_reference_t < T > > || 
	is_same_v < short , remove_reference_t < T > > ||
	is_same_v < int   , remove_reference_t < T > > ||
	is_same_v < long  , remove_reference_t < T > > > {}; // note: not full list

template < typename T > inline constexpr auto is_integral_v = is_integral < T > ::value;

// =================================================================================================

template < typename T > struct is_pointer               : std::false_type {};
template < typename T > struct is_pointer < T *       > : std:: true_type {};
template < typename T > struct is_pointer < T * const > : std:: true_type {};

template < typename T > inline constexpr auto is_pointer_v = is_pointer < T > ::value;

// =================================================================================================

template < typename T                > struct is_array          : public std::false_type {};
template < typename T                > struct is_array < T[ ] > : public std:: true_type {};
template < typename T, std::size_t N > struct is_array < T[N] > : public std:: true_type {};

template < typename T > inline constexpr auto is_array_v = is_array < T > ::value;

// =================================================================================================

template < typename  T                     > struct is_function                  : std::false_type {};
template < typename RT, typename ... Types > struct is_function < RT(Types...) > : std:: true_type {};

// note: const, volatile, &, && and noexcept produce very long list of combinations 

template < typename T > inline constexpr auto is_function_v = is_function < T > ::value;

// =================================================================================================

template < typename D, typename B > class is_derived
{
private:

	class N { std::byte data[1]; }; // note: sizeof(N) is 1
	class Y { std::byte data[2]; }; // note: sizeof(Y) is 2

private:

	static constexpr N test(...); // note: C-style for inheritance
	static constexpr Y test(B *);

public:

	static constexpr auto value = (sizeof(test(static_cast < D * > (nullptr))) == sizeof(Y));

}; // template < typename D, typename B > class is_derived

template < typename D, typename B > inline constexpr auto is_derived_v = is_derived < D, B > ::value;

// =================================================================================================

namespace detail
{
	template < typename T > std::false_type detect_is_polymorphic(...); // note: C-style for inheritance

    template < typename T > std:: true_type detect_is_polymorphic(decltype(
		dynamic_cast < void * > (static_cast < T * > (nullptr)))); // note: SFINAE based on dynamic_cast

} // namespace detail
 
template < typename T > struct is_polymorphic : decltype(detail::detect_is_polymorphic < T > (nullptr)) {};

template < typename T > inline constexpr auto is_polymorphic_v = is_polymorphic < T > ::value;

// =================================================================================================

class Base { public: virtual ~Base() = default; }; // note: polymorphic base class

class Derived : public Base {}; 

class Single {};

// =================================================================================================

template < bool B, typename T = void > struct enable_if             {                 }; // note: nothing
template <         typename T        > struct enable_if < true, T > { using type = T; };

template < bool B, typename T = void > using  enable_if_t = typename enable_if < B, T > ::type;

// =================================================================================================

template < bool C, typename T, typename F > struct conditional                 { using type = T; };
template <         typename T, typename F > struct conditional < false, T, F > { using type = F; };

template < bool C, typename T, typename F > using  conditional_t = typename conditional < C, T, F > ::type;

// =================================================================================================

int main()
{
	static_assert( is_same_v < int, int    > );
	static_assert(!is_same_v < int, double > );

	static_assert( is_homogeneous_v < int, int, int    > );
	static_assert(!is_homogeneous_v < int, int, double > );

	static_assert(!is_lvalue_reference_v < int    > );
	static_assert( is_lvalue_reference_v < int &  > );
	static_assert(!is_lvalue_reference_v < int && > );

	static_assert(!is_rvalue_reference_v < int    > );
	static_assert(!is_rvalue_reference_v < int &  > );
	static_assert( is_rvalue_reference_v < int && > );

	static_assert( is_same_v <     remove_reference_t < int    > , int    > );
	static_assert( is_same_v <     remove_reference_t < int &  > , int    > );
	static_assert( is_same_v <     remove_reference_t < int && > , int    > );

	static_assert( is_same_v < add_lvalue_reference_t < int    > , int &  > );
	static_assert( is_same_v < add_rvalue_reference_t < int    > , int && > );

	static_assert( is_integral_v < int    > );
	static_assert(!is_integral_v < double > );

	static_assert(!is_pointer_v < int         > );
	static_assert( is_pointer_v < int *       > );
	static_assert( is_pointer_v < int * const > );

	static_assert(!is_array_v < int    > );
	static_assert( is_array_v < int[ ] > );
	static_assert( is_array_v < int[5] > );

	static_assert(!is_function_v < int           > );
	static_assert( is_function_v < int(int     ) > );
	static_assert( is_function_v < int(int, int) > );

	static_assert( is_derived_v < Derived, Base > );
	static_assert(!is_derived_v <  Single, Base > );

	static_assert( is_polymorphic_v < Base    > );
	static_assert( is_polymorphic_v < Derived > );
	static_assert(!is_polymorphic_v < Single  > );

	static_assert( is_same_v < enable_if_t < 1 + 1 == 2, int > , int > );
//	static_assert(!is_same_v < enable_if_t < 1 + 1 != 2, int > , int > ); // error: no alternatives

	static_assert( is_same_v < conditional_t < 1 + 1 == 2, int, double > , int    > );
	static_assert( is_same_v < conditional_t < 1 + 1 != 2, int, double > , double > );

	return 0;
}