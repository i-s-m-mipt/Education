#include <cstddef>
#include <cstdint>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > class is_same          : public std::false_type {};

template < typename T               > class is_same < T, T > : public std:: true_type {};

template < typename T1, typename T2 > constexpr auto is_same_v = is_same < T1, T2 > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T, typename ... Ts 
> 
constexpr auto is_any_of_v = (is_same_v < T, Ts > || ...);

///////////////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T, typename ... Ts 
> 
constexpr auto is_all_of_v = (is_same_v < T, Ts > && ...);

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class is_lvalue_reference          : public std::false_type {};

template < typename T > class is_lvalue_reference < T & >  : public std:: true_type {};

template 
< 
	typename T 
> 
constexpr auto is_lvalue_reference_v = is_lvalue_reference < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class is_rvalue_reference          : public std::false_type {};

template < typename T > class is_rvalue_reference < T && > : public std:: true_type {};

template 
< 
	typename T 
> 
constexpr auto is_rvalue_reference_v = is_rvalue_reference < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct remove_reference          { using type = T; };

template < typename T > struct remove_reference < T &  > { using type = T; };

template < typename T > struct remove_reference < T && > { using type = T; };

template < typename T > using  remove_reference_t = typename remove_reference < T > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct add_lvalue_reference { using type = T & ; };

template < typename T > struct add_rvalue_reference { using type = T &&; };

template < typename T > using  add_lvalue_reference_t = typename add_lvalue_reference < T > ::type;

template < typename T > using  add_rvalue_reference_t = typename add_rvalue_reference < T > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class is_integral : public std::integral_constant 
< 
	bool, is_same_v < bool  , remove_reference_t < T > > || 
		  is_same_v < char  , remove_reference_t < T > > || 
		  is_same_v < short , remove_reference_t < T > > ||
		  is_same_v < int   , remove_reference_t < T > > ||
		  is_same_v < long  , remove_reference_t < T > > 
> {};

template < typename T > constexpr auto is_integral_v = is_integral < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class is_pointer         : public std::false_type {};

template < typename T > class is_pointer < T * > : public std:: true_type {};

template < typename T > constexpr auto is_pointer_v = is_pointer < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T                > class is_array          : public std::false_type {};

template < typename T                > class is_array < T[ ] > : public std:: true_type {};

template < typename T, std::size_t S > class is_array < T[S] > : public std:: true_type {};

template < typename T > constexpr auto is_array_v = is_array < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename B > class is_derived
{
private:

	static std::int32_t test(...);

	static std::int64_t test(B *);

public:

	static constexpr auto value = sizeof(test(static_cast < D * > (nullptr))) == 8;
};

template 
< 
	typename D, typename B 
> 
constexpr auto is_derived_v = is_derived < D, B > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > add_rvalue_reference_t < T > declval();

class Bad 
{ 
private:

	Bad() = default; 
};

int test(Bad);

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename B > class is_polymorphic
{
private:

	template < typename T > static std::false_type test(...);

    template < typename T > static std:: true_type test
	(
		int, decltype(dynamic_cast < void * > (std::declval < T * > ())) = nullptr
	);

public:
      
	static constexpr auto value = decltype(test < B > (0))::value;
};

template < typename B > constexpr auto is_polymorphic_v = is_polymorphic < B > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename B > class is_convertible
{
private:

    template < typename U > static int helper(U);

//  ---------------------------------------------------------------------

	template < typename T, typename U > static std::false_type test(...);

    template < typename T, typename U > static std:: true_type test
	(
		int, decltype(helper < U > (std::declval < T > ())) = 0
	);

public:
      
	static constexpr auto value = decltype(test < D, B > (0))::value;
};

template 
< 
	typename D, typename B 
> 
constexpr auto is_convertible_v = is_convertible < D, B > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

class Entity 
{ 
public:

	virtual ~Entity() = default; 
};

class Client : public Entity {}; 

class Server 
{ 
public:

	explicit Server(int) {} 
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template < bool C, typename T = void > struct enable_if             {                 };

template <         typename T        > struct enable_if < true, T > { using type = T; };

template < bool C, typename T = void > using  enable_if_t = typename enable_if < C, T > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < bool C, typename T, typename F > struct conditional                 { using type = T; };

template <         typename T, typename F > struct conditional < false, T, F > { using type = F; };

template 
< 
	bool C, typename T, typename F 
> 
using conditional_t = typename conditional < C, T, F > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		static_assert(is_same_v < int, int > && !is_same_v < int, double > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert( is_any_of_v < int, int, double > );

		static_assert(!is_all_of_v < int, int, double > );
	}
	
//  ------------------------------------------------------------------------------------------

	{
		static_assert(!is_lvalue_reference_v < int    > );

		static_assert( is_lvalue_reference_v < int &  > );

		static_assert(!is_lvalue_reference_v < int && > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert(!is_rvalue_reference_v < int    > );

		static_assert(!is_rvalue_reference_v < int &  > );

		static_assert( is_rvalue_reference_v < int && > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert(std::is_same_v < remove_reference_t < int    > , int > );

		static_assert(std::is_same_v < remove_reference_t < int &  > , int > );

		static_assert(std::is_same_v < remove_reference_t < int && > , int > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert(std::is_same_v < add_lvalue_reference_t < int > , int &  > );

		static_assert(std::is_same_v < add_rvalue_reference_t < int > , int && > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert( is_integral_v < int    > );
		
		static_assert(!is_integral_v < double > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert( is_pointer_v < int * > );
		
		static_assert(!is_pointer_v < int   > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert( is_array_v < int[5] > );

		static_assert( is_array_v < int[ ] > );

		static_assert(!is_array_v < int    > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert( is_derived_v < Client, Entity > );

		static_assert(!is_derived_v < Server, Entity > );

//		static_assert( is_derived_v < Client, Client > ); // bad
	}

//  ------------------------------------------------------------------------------------------

	{
		[[maybe_unused]] decltype(test(declval < Bad > ())) x = 1;
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert( is_polymorphic_v < Entity > );

		static_assert( is_polymorphic_v < Client > );

		static_assert(!is_polymorphic_v < Server > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert( is_convertible_v < int      , double   > );

		static_assert(!is_convertible_v < int      , Server   > );

		static_assert( is_convertible_v < Client * , Entity * > );

		static_assert(!is_convertible_v < Server * , Entity * > );
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert( std::is_same_v < enable_if_t < 1 + 2 == 3, int > , int > );

//		static_assert(!std::is_same_v < enable_if_t < 1 + 2 != 3, int > , int > ); // error
	}

//  ------------------------------------------------------------------------------------------

	{
		static_assert(std::is_same_v < conditional_t < 1 + 2 == 3, int, double > , int    > );

		static_assert(std::is_same_v < conditional_t < 1 + 2 != 3, int, double > , double > );
	}	
}