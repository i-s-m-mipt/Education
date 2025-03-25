#include <cassert>
#include <memory>
#include <utility>

////////////////////////////////////////////////////////////////

class Entity
{
public :

	void test()
	{ 
		[[maybe_unused]] auto lambda = [this](){ m_x = 1; };
	}

private :

	int m_x = 0;
};

////////////////////////////////////////////////////////////////

int main()
{
	auto x = 1, y = 2;

	auto lambda_1 = [&x, y]() mutable { x = ++y; };

//  ------------------------------------------------------------

	lambda_1();

//  ------------------------------------------------------------
		
	assert(x == 3 && y == 2);

//  ------------------------------------------------------------

//	[[maybe_unused]] auto lambda_2 = [&](){}; // bad

//	[[maybe_unused]] auto lambda_3 = [=](){}; // bad

//  ------------------------------------------------------------

	auto z1 = std::make_unique < int > (3);

	auto lambda_4 = [z2 = std::move(z1)](){ assert(*z2 == 3); };

	lambda_4();

//  ------------------------------------------------------------

	Entity().test();
}