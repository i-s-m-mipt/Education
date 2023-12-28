module; // note: global module fragment

#include <iostream>

module math; // note: implementation unit

void hello_module()
{
	std::cout << "Hello, module!" << std::endl;
}