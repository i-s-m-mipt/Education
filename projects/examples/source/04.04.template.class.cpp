#include <cassert>
#include <deque>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

//  ================================================================================================

template < typename T, typename C = std::vector < T > > class Stack_v1
{
public:

	void push(T data);

	auto top() const;

	void pop();

private:

	C m_container;
};

//  ================================================================================================

template < typename T, typename C > void Stack_v1 < T, C > ::push(T data)
{
	m_container.push_back(std::move(data));
}

template < typename T, typename C > auto Stack_v1 < T, C > ::top() const
{
	return m_container.back();
}

template < typename T, typename C > void Stack_v1 < T, C > ::pop()
{
	m_container.pop_back();
}

//  ================================================================================================

template < typename T, template < typename T > typename C = std::vector > class Stack_v2 
{
private:

	C < T > m_container;
};

//  ================================================================================================

template 
< 
	template < typename T > typename C1,
	
	template < typename T > typename C2, typename T 
>		   
auto copy(const C1 < T > & container)
{
	return C2 < T > (std::begin(container), std::end(container));
}

//  ================================================================================================

template < typename T1, typename T2 > struct Pair 
{ 
	T1 data_1 = T1(); 
	
	T2 data_2 = T2(); 
};

//  ================================================================================================

template < typename T1, typename T2 > class Entity
{
public:

	void test() const
	{ 
		std::cout << "Entity::test (1)\n"; 
	}
};

template < typename T > class Entity < T, T >
{
public:

	void test() const 
	{ 
		std::cout << "Entity::test (2)\n"; 
	}
};

template < typename T > class Entity < T, int >
{
public:

	void test() const 
	{ 
		std::cout << "Entity::test (3)\n"; 
	}
};

template < typename T1, typename T2 > class Entity < T1 * , T2 * >
{
public:

	void test() const 
	{ 
		std::cout << "Entity::test (4)\n"; 
	}
};

template <> class Entity < int, std::string >
{
public:

	void test() const 
	{ 
		std::cout << "Entity::test (5)\n"; 
	}
};

//  ================================================================================================

int main()
{
	{
		Stack_v1 < int > stack_v1;

		stack_v1.push(1); 
	
		assert(stack_v1.top() == 1); 
	
		stack_v1.pop();
	}
	
//  ---------------------------------------------------------------------------

	{
		Stack_v1 < double, std::deque < double > > stack_v1;
	
		Stack_v2 < double, std::deque > stack_v2;
	}

//  ---------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		auto deque = copy < std::vector, std::deque > (vector);
	}

//  ---------------------------------------------------------------------------

	{
		[[maybe_unused]] Pair pair(1, 1);

		std::vector vector = { 1, 2, 3, 4, 5 };
	}

//  ---------------------------------------------------------------------------

	{
		using type_1 = int;

		using type_2 = std::string;

		using type_3 = double;

		Entity < type_1   , type_3   > ().test();
		Entity < type_2   , type_2   > ().test();
		Entity < type_2   , type_1   > ().test();
		Entity < type_1 * , type_2 * > ().test();
		Entity < type_1   , type_2   > ().test();
//		Entity < type_1   , type_1   > ().test(); // error
//		Entity < type_1 * , type_1 * > ().test(); // error
	}
}