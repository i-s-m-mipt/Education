#include <functional>
#include <vector>

///////////////////////////////////////////////////////////////

int main()
{
    std::vector < std::function < int(int, int) > > functions =
	{
		[](auto x, auto y){ return x + y; },

		[](auto x, auto y){ return x - y; },

		[](auto x, auto y){ return x * y; },

		[](auto x, auto y){ return x / y; }
	};
}