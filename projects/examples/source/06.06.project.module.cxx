module;

#define DEBUG(data) std::cout << __func__ << " : " << data << '\n'

import <iostream>;

export module demo;

export import demo.submodule;

export namespace demo
{
	void test_v1() { std::clog << "demo::test_v1\n"; }

	void test_v2();
}

namespace demo
{
	void test_v4() { std::clog << "demo::test_v4\n"; }
}