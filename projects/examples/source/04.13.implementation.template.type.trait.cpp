#include <cstddef>
#include <type_traits>
#include <utility>

//  ================================================================================================

template < typename T1, typename T2 > struct is_same            : public std::false_type {};
template < typename T1              > struct is_same < T1, T1 > : public std:: true_type {};

template < typename T1, typename T2 > inline constexpr auto is_same_v = is_same < T1, T2 > ::value;

template < typename T1, typename ... Ts > 

inline constexpr auto is_any_of_v = (is_same_v < T1, Ts > || ...);

template < typename T1, typename ... Ts > 

inline constexpr auto is_all_of_v = (is_same_v < T1, Ts > && ...);

//  ================================================================================================

template < typename T > struct is_void          : public std::false_type {};
template <            > struct is_void < void > : public std:: true_type {};

template < typename T > inline constexpr auto is_void_v = is_void < T > ::value;

//  ================================================================================================

template < typename T > struct  is_lvalue_reference          : public std::false_type {};
template < typename T > struct  is_lvalue_reference < T & >  : public std:: true_type {};

template < typename T > 

inline constexpr auto is_lvalue_reference_v = is_lvalue_reference < T > ::value;

template < typename T > struct  is_rvalue_reference          : public std::false_type {};
template < typename T > struct  is_rvalue_reference < T && > : public std:: true_type {};

template < typename T > 

inline constexpr auto is_rvalue_reference_v = is_rvalue_reference < T > ::value;

//  ================================================================================================

template < typename T > struct remove_reference          { using type = T; };
template < typename T > struct remove_reference < T &  > { using type = T; };
template < typename T > struct remove_reference < T && > { using type = T; };

template < typename T > using  remove_reference_t = typename remove_reference < T > ::type;

//  ================================================================================================

template < typename T > struct add_lvalue_reference { using type = T & ; };
template < typename T > struct add_rvalue_reference { using type = T &&; };

template < typename T > using  add_lvalue_reference_t = typename add_lvalue_reference < T > ::type;
template < typename T > using  add_rvalue_reference_t = typename add_rvalue_reference < T > ::type;

//  ================================================================================================

template < typename T > struct is_integral : public std::integral_constant < bool,

    is_same_v < bool  , remove_reference_t < T > > || 
	is_same_v < char  , remove_reference_t < T > > || 
	is_same_v < short , remove_reference_t < T > > ||
	is_same_v < int   , remove_reference_t < T > > ||
	is_same_v < long  , remove_reference_t < T > > > {}; // demo: неполный список

template < typename T > inline constexpr auto is_integral_v = is_integral < T > ::value;

//  ================================================================================================

template < typename T > struct is_pointer         : public std::false_type {};
template < typename T > struct is_pointer < T * > : public std:: true_type {};

template < typename T > inline constexpr auto is_pointer_v = is_pointer < T > ::value;

//  ================================================================================================

template < typename T                > struct is_array          : public std::false_type {};
template < typename T                > struct is_array < T[ ] > : public std:: true_type {};
template < typename T, std::size_t N > struct is_array < T[N] > : public std:: true_type {};

template < typename T > inline constexpr auto is_array_v = is_array < T > ::value;

//  ================================================================================================

template < typename D, typename B > class is_derived // support: реализация Герба Саттера
{
private:

	class N { const std::byte data[1]{}; };
	class Y { const std::byte data[2]{}; };

private:

	[[nodiscard]] static constexpr N test(...); // support: эллипсис из языка C
	[[nodiscard]] static constexpr Y test(B *);

public:

	static constexpr auto value = (sizeof(test(static_cast < D * > (nullptr))) == sizeof(Y));

}; // template < typename D, typename B > class is_derived

template < typename D, typename B > 

inline constexpr auto is_derived_v = is_derived < D, B > ::value;

//  ================================================================================================

template < typename T > add_rvalue_reference_t < T > declval() { static_assert(false); }

//  ================================================================================================

class Bad { private: Bad() {} };

[[nodiscard]] inline constexpr int f(Bad);

//  ================================================================================================

template < typename T > class is_polymorphic
{
private:

	template < typename T1 > [[nodiscard]] static constexpr std::false_type test(...);
    template < typename T1 > [[nodiscard]] static constexpr std:: true_type test(int, 

		decltype(dynamic_cast < void * > (declval < T1 * > ())) = nullptr);

public:
      
	static constexpr auto value = decltype(test < T > (0))::value;

}; // template < typename T > class is_polymorphic

template < typename T > inline constexpr auto is_polymorphic_v = is_polymorphic < T > ::value;

//  ================================================================================================

template < typename F, typename T > class is_convertible
{
private:

    template < typename T1 > static constexpr int helper_consumer(T1);

private:

	template < typename F1, typename T1 > [[nodiscard]] static constexpr std::false_type test(...);
    template < typename F1, typename T1 > [[nodiscard]] static constexpr std:: true_type test(int, 
	
		decltype(helper_consumer < T1 > (declval < F1 > ())) = 0);

public:
      
	static constexpr auto value = decltype(test < F, T > (0))::value;

}; // template < typename F, typename T > class is_convertible

template < typename F, typename T > 

inline constexpr auto is_convertible_v = is_convertible < F, T > ::value;

//  ================================================================================================

class B { public: virtual ~B() {} };

class D : public B {}; 

class C {};

//  ================================================================================================

template < bool V, typename T = void > struct enable_if             {                 };
template <         typename T        > struct enable_if < true, T > { using type = T; };

template < bool V, typename T = void > using  enable_if_t = typename enable_if < V, T > ::type;

//  ================================================================================================

template < bool V, typename T, typename F > struct conditional                 { using type = T; };
template <         typename T, typename F > struct conditional < false, T, F > { using type = F; };

template < bool V, typename T, typename F > 

using conditional_t = typename conditional < V, T, F > ::type;

//  ================================================================================================

int main()
{
	static_assert( is_same_v   <      int, int    > );
	static_assert(!is_same_v   <      int, double > );

	static_assert( is_any_of_v < int, int, int    > );
	static_assert( is_any_of_v < int, int, double > );

	static_assert( is_all_of_v < int, int, int    > );
	static_assert(!is_all_of_v < int, int, double > );

//  ================================================================================================

	static_assert(!is_lvalue_reference_v < int    > );
	static_assert( is_lvalue_reference_v < int &  > );
	static_assert(!is_lvalue_reference_v < int && > );

	static_assert(!is_rvalue_reference_v < int    > );
	static_assert(!is_rvalue_reference_v < int &  > );
	static_assert( is_rvalue_reference_v < int && > );

//  ================================================================================================

	static_assert( is_same_v <     remove_reference_t < int    > , int    > );
	static_assert( is_same_v <     remove_reference_t < int &  > , int    > );
	static_assert( is_same_v <     remove_reference_t < int && > , int    > );

	static_assert( is_same_v < add_lvalue_reference_t < int    > , int &  > );
	static_assert( is_same_v < add_rvalue_reference_t < int    > , int && > );

//  ================================================================================================

	static_assert( is_integral_v < int    > );
	static_assert(!is_integral_v < double > );

	static_assert(!is_pointer_v  < int    > );
	static_assert( is_pointer_v  < int *  > );

	static_assert(!is_array_v    < int    > );
	static_assert( is_array_v    < int[ ] > );
	static_assert( is_array_v    < int[5] > );

//  ================================================================================================

	static_assert( is_derived_v < D, B > );
	static_assert(!is_derived_v < C, B > );

	[[maybe_unused]] decltype(f(declval < Bad > ())) variable{};

	static_assert( is_polymorphic_v < B > );
	static_assert( is_polymorphic_v < D > );
	static_assert(!is_polymorphic_v < C > );

	static_assert( is_convertible_v < D * , B * > );
	static_assert(!is_convertible_v < C * , B * > );

//  ================================================================================================

	static_assert( is_same_v < enable_if_t   < 1 + 1 == 2, int         > , int    > );
//	static_assert(!is_same_v < enable_if_t   < 1 + 1 != 2, int         > , int    > ); // error

	static_assert( is_same_v < conditional_t < 1 + 1 == 2, int, double > , int    > );
	static_assert( is_same_v < conditional_t < 1 + 1 != 2, int, double > , double > );

	return 0;
}