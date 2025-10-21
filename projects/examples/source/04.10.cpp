//////////////////////////////////////////////////

#include <print>

//////////////////////////////////////////////////

template < typename T1, typename T2 > class Entity
{
public :

	void test() const
	{ 
		std::print("Entity::test (1)\n");
	}
};

//////////////////////////////////////////////////

template < typename T > class Entity < T, int >
{
public :

	void test() const 
	{ 
		std::print("Entity::test (2)\n");
	}
};

//////////////////////////////////////////////////

template < typename T > class Entity < T, T >
{
public :

	void test() const 
	{ 
		std::print("Entity::test (3)\n");
	}
};

//////////////////////////////////////////////////

template <> class Entity < double, double >
{
public :

	void test() const 
	{ 
		std::print("Entity::test (4)\n");
	}
};

//////////////////////////////////////////////////

int main()
{
	Entity < int,    double > ().test();

	Entity < double, int    > ().test();

//	Entity < int,    int    > ().test(); // error

	Entity < double, double > ().test();
}

//////////////////////////////////////////////////