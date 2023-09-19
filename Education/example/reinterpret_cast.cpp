#include <iostream>
#include <memory>

int main()
{
	auto ptr_i = new int(97);

	auto ptr_c = reinterpret_cast < char * > (ptr_i);

	std::cout << *ptr_i << std::endl;
	std::cout << *ptr_c << std::endl;

	auto ptr_d = new double(1234.5678);

	std::cout.write(reinterpret_cast < const char * > (ptr_d), sizeof(double));

	return 0;
}