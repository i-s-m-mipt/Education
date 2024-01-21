module; // note: global module fragment

#include <iostream>

export module math.submodule;

export void hello_submodule()
{
	std::cout << "Hello, submodule!" << std::endl;
}