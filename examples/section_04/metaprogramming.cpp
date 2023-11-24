#include <iostream>

template < int p, int d > struct Check_Is_Prime
{
	static const bool value = (p % d != 0) && Check_Is_Prime < p, d - 1 > ::value;

}; // template < int p, int d > struct Check_Is_Prime

template < int p > struct Check_Is_Prime < p, 2 >
{
	static const bool value = (p % 2 != 0);

}; // template < int p > struct Check_Is_Prime < p, 2 >

template < int p > struct Is_Prime
{
	static const bool value = Check_Is_Prime < p, p / 2 > ::value;

}; // template < int p > struct Is_Prime

template <> struct Is_Prime < 0 > {	static const bool value = false; };
template <> struct Is_Prime < 1 > { static const bool value = false; };
template <> struct Is_Prime < 2 > { static const bool value =  true; };
template <> struct Is_Prime < 3 > { static const bool value =  true; };

template < int p > const bool is_prime_v = Is_Prime < p > ::value; // good: variable template

int main()
{
	std::cout << is_prime_v < 42 > << std::endl;
	std::cout << is_prime_v < 43 > << std::endl;

	return 0;
}