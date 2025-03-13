#include <iostream>
#include <typeinfo>
#include <tuple>

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto lambda_1 = [](){}; // support: cppinsights.io

    auto lambda_2 = [] < typename T > (T x, T y){ return x < y ? y : x; };

	auto lambda_3 = [](auto x) constexpr noexcept { return x; };

//  -----------------------------------------------------------------------------

	std::ignore = lambda_2(1, 2);

//	std::ignore = lambda_2(1, 2.0); // error

//  -----------------------------------------------------------------------------

	std::cout << "main : typeid(lambda_1) = " << typeid(lambda_1).name() << '\n';

	std::cout << "main : typeid(lambda_2) = " << typeid(lambda_2).name() << '\n';

    std::cout << "main : typeid(lambda_3) = " << typeid(lambda_3).name() << '\n';
}