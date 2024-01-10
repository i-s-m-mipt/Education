#include <iostream>
#include <string>

void generate_slow(std::size_t n, std::string s = "", std::size_t l = 0, std::size_t r = 0)
{
	if (l == n && r == n)
	{
		std::cout << s << std::endl; // note: slow output with std::endl
	}
	else
	{
		if (l < n)
		{
			generate_slow(n, s + '(', l + 1, r);
		}

		if (r < l)
		{
			generate_slow(n, s + ')', l, r + 1);
		}
	}
}

void generate_fast(std::size_t n, std::string & output, std::string s = "", std::size_t l = 0, std::size_t r = 0)
{
	if (l < n)
	{
		for (auto i = n; i > std::max(l, r + 1) - 1; --i) // good: loop instead of recursive calls
		{
			generate_fast(n, output, s + std::string(i - l, '(') + ')', i, r + 1);
		}
	}
	else
	{
		output += (s + std::string(n - r, ')') + '\n'); // good: batch of brackets
	}
}

int main()
{
	std::cout << "Enter number of brackets: "; std::size_t n{}; std::cin >> n;

//	generate_slow(n); // bad: slow function due to suboptimal operations

	std::string output;

	generate_fast(n, output);

	std::cout << output; // good: one output instead of many with std::endl

	return 0;
}