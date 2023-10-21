import std;

int main()
{
	char c = 'a';

	std::cout << static_cast < int > (c) << std::endl;

	std::cout << sizeof(char) << std::endl; // note: guaranteed size 8 bits

	std::cout << std::boolalpha << std::is_signed_v < char > << std::endl;

	c = 255;

//	int x = c; // bad: undefined behavior, 255 or -1

	[[maybe_unused]] signed char sc = 'a';
	
	for (auto i = -128; i < 128; ++i) // note: two's complement representation
	{
		std::cout << static_cast < char > (i);
	}

	std::cout << std::endl;

	[[maybe_unused]] unsigned char uc = 'a';

	for (auto i = 0; i < 256; ++i) // note: two's complement representation
	{
		std::cout << static_cast < char > (i);
	}

	std::cout << std::endl;

	for (auto pc = '!'; pc <= '~'; ++pc) // note: all printable ASCII characters
	{
		std::cout << pc;
	}

	std::cout << std::endl;
	
	std::cout << '8' - '0' << std::endl; // note: obtain integer digit from character digit

	[[maybe_unused]] wchar_t wc; // note: used for wide encodings, non-portable type

	std::cout << sizeof(wchar_t) << std::endl; // note: usually 16 or 32 bits

	[[maybe_unused]] char8_t c8; // note: used for UTF-8 encoding

	std::cout << sizeof(char8_t) << std::endl; // note: 8 bits

	[[maybe_unused]] char16_t c16; // note: used for UTF-16 encoding

	std::cout << sizeof(char16_t) << std::endl; // note: 16 bits
	
	[[maybe_unused]] char32_t c32; // note: used for UTF-32 encoding

	std::cout << sizeof(char32_t) << std::endl; // note: 32 bits

	return 0;
}