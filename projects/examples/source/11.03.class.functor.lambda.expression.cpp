#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto lambda_1 = [](){}; // support: cppinsights.io

		auto lambda_2 = [](auto x) constexpr noexcept { return x; };

		std::cout << "main : typeid(lambda_1) = " << typeid(lambda_1).name() << '\n';

		std::cout << "main : typeid(lambda_2) = " << typeid(lambda_2).name() << '\n';
	}
	
//  ---------------------------------------------------------------------------------

	{
		auto x = 1, y = 2;

		[&x, y]() mutable { x = ++y; }(); assert(x == 3 && y == 2);

//		[&](){ x = y; }(); // bad

		auto ptr_1 = std::make_unique < int > (1);

		[ptr_2 = std::move(ptr_1)](){ assert(*ptr_2 == 1); }();

		Entity().test();
	}

//  ---------------------------------------------------------------------------------

	{
		std::array < std::function < int(int, int) > , 5 > functions = 
		{
			[](auto x, auto y){ return x + y; },

			[](auto x, auto y){ return x - y; },

			[](auto x, auto y){ return x * y; },

			[](auto x, auto y){ return x / y; },

			[](auto x, auto y){ return x % y; }
		};

		auto x = 1, y = 2;

		assert(functions.at(0)(x, y) == (x + y));
	}

//  ---------------------------------------------------------------------------------

	{
		auto lambda = [] < typename T > (T x, T y){ return x + y; };

		std::ignore = lambda(1, 2);

//		std::ignore = lambda(1, 2.0); // error
	}

//  ---------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::ranges::transform(vector, std::begin(vector), [](auto x){ return -x; });

		assert(vector == std::vector < int > ({ -1, -2, -3, -4, -5 }));
	}

//  ---------------------------------------------------------------------------------

	{
		auto lambda = [](auto lhs, auto rhs){ return lhs < rhs; };

		std::set < int, decltype(lambda) > set = { 5, 4, 3, 2, 1 };

		assert(std::ranges::is_sorted(set));
	}	
}