#include <iostream>

namespace library_v1
{
	[[nodiscard]] int f(int x)
	{
		std::cout << "Hello, static library!" << std::endl;

		return x;
	}

} // namespace library_v1