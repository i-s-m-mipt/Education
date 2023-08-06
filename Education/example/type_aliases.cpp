#include <cstdint>
#include <iostream>
#include <type_traits>

int main()
{
	using integer_t = unsigned long;

	integer_t value = 0;

	const std::size_t size = 1'000'000;

	for (std::size_t i = 0; i < size; ++i) {}

	std::int16_t x = 0;

	std::cout << std::boolalpha << std::is_same_v < int, std::int32_t > << std::endl;

	std::cout << sizeof(std::uint64_t) << std::endl;

	return 0;
}