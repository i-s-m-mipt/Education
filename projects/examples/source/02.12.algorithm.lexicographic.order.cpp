#include <iostream>
#include <string>

//  ================================================================================================

void generate_slow(std::size_t size, std::string s = "", std::size_t l = 0, std::size_t r = 0)
{
	if (l == size && r == size)
	{
		std::cout << s << std::endl;
	}
	else
	{
		if (l < size) generate_slow(size, s + '(', l + 1, r    );
		if (r < l   ) generate_slow(size, s + ')', l    , r + 1);
	}
}

//  ================================================================================================

void generate_fast(std::size_t size, std::string & output, std::string s = "", std::size_t l = 0, 
																			   std::size_t r = 0)
{
	if (l < size)
	{
		for (auto i = size; i > std::max(l, r + 1) - 1; --i)
		{
			generate_fast(size, output, s + std::string(i - l, '(') + ')', i, r + 1);
		}
	}
	else output += (s + std::string(size - r, ')') + '\n');
}

//  ================================================================================================

int main()
{
	const std::size_t size = 5;

//	generate_slow(size); // bad: медленная реализация

	std::string output;

	generate_fast(size, output);

	std::cout << output;

	return 0;
}