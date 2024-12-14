module;

#define DEBUG(data) std::cout << __func__ << " : " << data << '\n'

export module demo;

export import demo.submodule;

import <iostream>;

export namespace demo
{
	void test_v1() { std::clog << "demo::test_v1\n"; }

	void test_v2();
}

namespace demo
{
	void test_v3() { std::clog << "demo::test_v3\n"; }
}