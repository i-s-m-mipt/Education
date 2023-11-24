#include <iostream>

template < int N > struct Factorial
{
	static const int value = N * Factorial < N - 1 > ::value;

}; // template < int N > struct Factorial

template <> struct Factorial < 0 > { static const int value = 1; };

template < int N > const int factorial_v = Factorial < N > ::value; // good: variable template

template < int P, int D > struct Check_Is_Prime
{
	static const bool value = (P % D != 0) && Check_Is_Prime < P, D - 1 > ::value;

}; // template < int P, int D > struct Check_Is_Prime

template < int P > struct Check_Is_Prime < P, 2 >
{
	static const bool value = (P % 2 != 0);

}; // template < int P > struct Check_Is_Prime < P, 2 >

template < int P > struct Is_Prime
{
	static const bool value = Check_Is_Prime < P, P / 2 > ::value;

}; // template < int p > struct Is_Prime

template <> struct Is_Prime < 0 > {	static const bool value = false; };
template <> struct Is_Prime < 1 > { static const bool value = false; };
template <> struct Is_Prime < 2 > { static const bool value =  true; };
template <> struct Is_Prime < 3 > { static const bool value =  true; };

template < int P > const bool is_prime_v = Is_Prime < P > ::value; // good: variable template

int main()
{
	std::cout << factorial_v < 5 > << std::endl;

	std::cout << is_prime_v < 42 > << std::endl;
	std::cout << is_prime_v < 43 > << std::endl;

	return 0;
}