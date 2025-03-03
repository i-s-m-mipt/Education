#include <cassert>
#include <deque>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

//////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > class Entity
{
public:

	void test() const
	{ 
		std::cout << "Entity::test (1)\n";
	}
};

//////////////////////////////////////////////////////////////////

template < typename T > class Entity < T, T >
{
public:

	void test() const 
	{ 
		std::cout << "Entity::test (2)\n";
	}
};

//////////////////////////////////////////////////////////////////

template < typename T > class Entity < T, int >
{
public:

	void test() const 
	{ 
		std::cout << "Entity::test (3)\n";
	}
};

//////////////////////////////////////////////////////////////////

template < typename T1, typename T2 > class Entity < T1 * , T2 * >
{
public:

	void test() const 
	{ 
		std::cout << "Entity::test (4)\n";
	}
};

//////////////////////////////////////////////////////////////////

template <> class Entity < int, std::string >
{
public:

	void test() const 
	{ 
		std::cout << "Entity::test (5)\n";
	}
};

//////////////////////////////////////////////////////////////////

int main()
{
	using type_1 = int;

	using type_2 = std::string;

	using type_3 = double;

//  --------------------------------------------------

	Entity < type_1   , type_3   > ().test();

	Entity < type_2   , type_2   > ().test();

	Entity < type_2   , type_1   > ().test();

	Entity < type_1 * , type_2 * > ().test();

	Entity < type_1   , type_2   > ().test();

//	Entity < type_1   , type_1   > ().test(); // error

//	Entity < type_1 * , type_1 * > ().test(); // error
}