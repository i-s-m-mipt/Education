#include <iostream>
#include <type_traits>

int main()
{
	std::cout << sizeof(char) << std::endl;

	std::cout << std::boolalpha << std::is_signed_v < char > << std::endl;

	for (int i = -128; i < 128; ++i) // for (int i = 0; i < 256; ++i)
	{
		std::cout << static_cast < char > (i) << '\n';
	}

	auto c = '8';

	std::cout << c - '0' << std::endl;

	system("pause");

	return 0;
}