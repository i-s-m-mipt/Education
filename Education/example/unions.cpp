#include <cstdlib>
#include <iomanip>
#include <iostream>

union Result
{
	std::uint16_t value_1;
	std::uint32_t value_2;
	std::uint64_t value_3 = 0xffffffffffffffff;
};

int main()
{
	Result result;

	result.value_1 = 0xabcd;

	std::cout << std::showbase << std::hex <<
		result.value_2 << std::endl <<
		result.value_3 << std::endl;

	return 0;
}