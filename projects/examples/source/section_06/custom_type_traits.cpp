#include <iostream>
#include <type_traits>

// =================================================================================================

template < typename T > struct remove_reference          { using type = T; };
template < typename T > struct remove_reference < T &  > { using type = T; };
template < typename T > struct remove_reference < T && > { using type = T; };

template < typename T > using remove_reference_t = typename remove_reference < T > ::type;

template < typename T > struct add_lvalue_reference { using type = T &  ; };
template < typename T > struct add_rvalue_reference { using type = T && ; };

template < typename T > using add_lvalue_reference_t = typename add_lvalue_reference < T > ::type;
template < typename T > using add_rvalue_reference_t = typename add_rvalue_reference < T > ::type;

// =================================================================================================

template < typename T1, typename T2 > struct is_same          : std::false_type {};
template < typename T               > struct is_same < T, T > : std:: true_type {};

template < typename T1, typename T2 > inline constexpr bool is_same_v = is_same < T1, T2 > ::value;

template < typename T > struct is_array : std::false_type {};

template < typename T, std::size_t N > struct is_array < T[N] > : std::true_type
{
	using type = T;

	static constexpr auto size = N;

}; // template < typename T, std::size_t N > struct is_array < T[N] > : std::true_type

template < typename T > struct is_array < T[] > : std::true_type
{
	using type = T;

	static constexpr auto size = 0;

}; // template < typename T > struct is_array < T[] > : std::true_type

template < typename T > inline constexpr bool is_array_v = is_array < T > ::value;

// =================================================================================================

template < typename D, typename B >
class Is_Derived
{
	class No {};
	class Yes { No no[2]; }; // Ðàçíûõ ðàçìåðîâ !

	static Yes test(B*);
	static No test(...); // ïðîèçâ. êîëè÷åñòâî àðãóìåíòîâ íåèçâåñòíûõ òèïîâ

public:

	// Ðàçðåøåíèå ïåðåãðóçêè âûïîëíÿåòñÿ âî âðåìÿ êîìïèëÿöèè
	// Îïðåäåëåíèå çàí÷åíèÿ sizeof âûïîëíÿåòñÿ âî âðåìÿ êîìïèëÿöèè
	// Çíà÷åíèå â enum âû÷èñÿëþòñÿ âî âðåìÿ êîìïèëÿöèè

	enum { value = sizeof(test(static_cast<D*>(0))) == sizeof(Yes) };
};

class B {};
class D : public B {};
class DD : public D {};
class E {};

template < bool C, typename True_Type, typename False_Type >
struct if_then_else
{
	using type = True_Type;
};

template < typename True_Type, typename False_Type >
struct if_then_else < false, True_Type, False_Type >
{
	using type = False_Type;
};

template < bool C, typename TT, typename FT >
using if_then_else_t = typename if_then_else < C, TT, FT >::type;

int main(int argc, char ** argv)
{
	std::cout << std::boolalpha;

	std::cout << std::is_base_of < B, D > ::value << std::endl;
	std::cout << std::is_base_of_v < B, DD > << std::endl;
	std::cout << std::is_base_of_v < B, E > << std::endl;

	std::cout << Is_Derived < D, B > ::value << std::endl;
	std::cout << Is_Derived < DD, B > ::value << std::endl;
	std::cout << Is_Derived < E, B > ::value << std::endl;

	//std::cout << is_same < int, float>::value << std::endl;
	//std::cout << is_same < int, int>::value << std::endl;

	//std::cout << is_array < int[10] > ::size << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}