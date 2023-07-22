#include <iostream>
#include <type_traits>

int main()
{
	std::cout << sizeof(char) << std::endl;

	std::cout << std::boolalpha << std::is_signed_v < char > << std::endl;

	signed   char c_1 = 'a';
	unsigned char c_2 = 'b';

	for (int i = -128; i < 128; ++i) // for (int i = 0; i < 256; ++i)
	{
		std::cout << static_cast < char > (i) << '\n';
	}

	for (char c = ' '; c <= '~'; ++c)
	{
		std::cout << c << '\n';
	}

	auto c = '8';

	std::cout << c - '0' << std::endl;

	system("pause");

	return 0;
}