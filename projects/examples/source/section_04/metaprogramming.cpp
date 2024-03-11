#include <iostream>

template < auto N > struct Factorial
{
	static const auto value = N * Factorial < N - 1 > ::value;
};

template <> struct Factorial < 0 > { static const auto value = 1; };

template < auto N > const auto factorial_v = Factorial < N > ::value;

template < auto P, auto D > struct Check_Is_Prime
{
	static const bool value = (P % D != 0) && Check_Is_Prime < P, D - 1 > ::value;
}; 

template < auto P > struct Check_Is_Prime < P, 2 >
{
	static const bool value = (P % 2 != 0);
}; 

template < auto P > struct Is_Prime
{
	static const bool value = Check_Is_Prime < P, P / 2 > ::value;
}; 

template <> struct Is_Prime < 0 > {	static const bool value = false; };
template <> struct Is_Prime < 1 > { static const bool value = false; };
template <> struct Is_Prime < 2 > { static const bool value =  true; };
template <> struct Is_Prime < 3 > { static const bool value =  true; };

template < auto P > const bool is_prime_v = Is_Prime < P > ::value;

int main()
{
	std::cout << factorial_v < 5 > << std::endl;

	std::cout << is_prime_v < 42 > << std::endl;
	std::cout << is_prime_v < 43 > << std::endl;

	return 0;
}