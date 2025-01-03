#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

	void test()
	{ 
		[this](){ m_data = 1; }(); 
	}

private:

	int m_data = 0;
};

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto lambda_1 = [](){}; // support: cppinsights.io

	auto lambda_2 = [](auto x) constexpr noexcept { return x; };

	std::cout << "main : typeid(lambda_1) = " << typeid(lambda_1).name() << '\n';
	std::cout << "main : typeid(lambda_2) = " << typeid(lambda_2).name() << '\n';

//  -----------------------------------------------------------------------------

	auto x = 1, y = 2, result = 0;

	[x, y, &result]()         { result = x + y; }();
	[x, y,  result]() mutable { result = x + y; }();

	assert(result == 3);

//	[&](){ result = x + y; }(); // bad

//  -----------------------------------------------------------------------------

	auto unique_ptr_1 = std::make_unique < int > (1);

	[unique_ptr_2 = std::move(unique_ptr_1)](){ assert(*unique_ptr_2 == 1); }(); 

//  -----------------------------------------------------------------------------

	std::array < std::function < int(int, int) > , 5 > functions;

	functions[0] = [](auto x, auto y){ return x + y; };
	functions[1] = [](auto x, auto y){ return x - y; };
	functions[2] = [](auto x, auto y){ return x * y; };
	functions[3] = [](auto x, auto y){ return x / y; };
	functions[4] = [](auto x, auto y){ return x % y; };

	assert(functions.at(0)(x, y) == (x + y));

//  -----------------------------------------------------------------------------

	auto lambda_3 = [] < typename T > (T x, T y){ return x + y; };

	std::ignore = lambda_3(1, 2);

//	std::ignore = lambda_3(1, 2.0); // error

//  -----------------------------------------------------------------------------

	std::vector < int > vector(5, 0);

	std::ranges::for_each(vector, [result](auto & x){       (x += result); });
	std::ranges::for_each(vector, [result](auto   x){ assert(x == result); });

//  -----------------------------------------------------------------------------

	auto lambda_6 = [](auto lhs, auto rhs){ return lhs < rhs; };

	std::set < int, decltype(lambda_6) > set({ 5, 4, 3, 2, 1 });

	assert(std::ranges::is_sorted(set));
}