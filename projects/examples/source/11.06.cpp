//////////////////////////////////////////////////////////////////////////

#include <print>

//////////////////////////////////////////////////////////////////////////

int main()
{
	auto lambda_1 = [](){}; // support : cppinsights.io

	auto lambda_2 = [](auto x) constexpr noexcept { return x; };

    auto lambda_3 = [] < typename T > (T x, T y){ return x < y ? y : x; };

//  ----------------------------------------------------------------------

	std::print("main : typeid(lambda_1) = {}\n", typeid(lambda_1).name());

	std::print("main : typeid(lambda_2) = {}\n", typeid(lambda_2).name());

    std::print("main : typeid(lambda_3) = {}\n", typeid(lambda_3).name());
}

//////////////////////////////////////////////////////////////////////////