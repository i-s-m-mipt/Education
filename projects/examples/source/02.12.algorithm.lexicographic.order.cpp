#include <iostream>
#include <string>

//  ================================================================================================

void generate_slow(std::size_t size, std::string s = "", std::size_t l = 0, std::size_t r = 0)
{
	if (l == size && r == size)
	{
		std::cout << s << std::endl; // note: slow output with std::endl
	}
	else
	{
		if (l < size) generate_slow(size, s + '(', l + 1, r    );
		if (r < l   ) generate_slow(size, s + ')', l    , r + 1);
	}
}

//  ================================================================================================

void generate_fast(std::size_t size, std::string & output, std::string s = "", std::size_t l = 0, std::size_t r = 0)
{
	if (l < size)
	{
		for (auto i = size; i > std::max(l, r + 1) - 1; --i) // good: loop instead of recursive calls
		{
			generate_fast(size, output, s + std::string(i - l, '(') + ')', i, r + 1);
		}
	}
	else output += (s + std::string(size - r, ')') + '\n'); // good: batch of brackets
}

//  ================================================================================================

int main()
{
	const std::size_t size = 5;

//	generate_slow(size); // bad: slow function due to suboptimal operations

	std::string output;

	generate_fast(size, output);

	std::cout << output; // good: single output instead of many with std::endl

	return 0;
}