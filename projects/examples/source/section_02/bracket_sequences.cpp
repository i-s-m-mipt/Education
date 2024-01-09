#include <iostream>
#include <string>

void generate_slow(std::size_t n, std::string s = "", std::size_t left = 0, std::size_t right = 0)
{
	if (left == n && right == n)
	{
		std::cout << s << std::endl; // note: slow output
	}
	else
	{
		if (left < n)
		{
			generate_slow(n, s + '(', left + 1, right);
		}

		if (right < left)
		{
			generate_slow(n, s + ')', left, right + 1);
		}
	}
}

void generate_fast(std::size_t n, std::string & output, std::string s = "", std::size_t left = 0, std::size_t right = 0)
{
	if (left < n)
	{
		for (auto i = n; i > std::max(left, right + 1) - 1; --i) // good: loop instead of recursion
		{
			generate_fast(n, output, s + std::string(i - left, '(') + ')', i, right + 1); // good: batch of (
		}
	}
	else
	{
		output += (s + std::string(n - right, ')') + '\n'); // good: batch of )
	}
}

int main()
{
	std::cout << "Enter number of brackets: "; std::size_t n{}; 

	std::cin >> n;

	generate_slow(n);

	std::cout << std::endl;

	std::string output;

	generate_fast(n, output);

	std::cout << output; // good: one output instead of many with std::endl

	return 0;
}