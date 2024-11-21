module;

import <iostream>;

export module demo.submodule;

export namespace demo
{
	void test_v3() 
	{ 
		std::clog << "demo::test_v3\n";
	}
}