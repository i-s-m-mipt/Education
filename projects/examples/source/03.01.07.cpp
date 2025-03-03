#include <iostream>
#include <string>

using namespace std::literals;

//////////////////////////////////////////////////////////

class Entity
{
public:

	static void test()
	{
		std::cout << "Entity::test\n";

	//	m_data = 1; // error
	}

//  ------------------------------------------------------

	static inline       auto s_data_1 = 0;

	static        const auto s_data_2 = 1;

//	static        const auto s_data_3 = "aaaaa"s; // error

	static inline const auto s_data_4 = "aaaaa"s;

private:

	int m_data = 0;
};

//////////////////////////////////////////////////////////

int main()
{
	Entity::s_data_1 = 1;

//  ---------------------

	Entity::test();
}