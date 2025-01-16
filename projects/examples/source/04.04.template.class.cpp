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

	void push(T value);

	auto top() const;

	void pop();

private:

	C m_data;
};

//  ================================================================================================

template < typename T, typename C > void Stack_v1 < T, C > ::push(T value)
{
	m_data.push_back(std::move(value));
}

template < typename T, typename C > auto Stack_v1 < T, C > ::top() const
{
	return m_data.back();
}

template < typename T, typename C > void Stack_v1 < T, C > ::pop()
{
	m_data.pop_back();
}

//  ================================================================================================

template < typename T, template < typename E > typename C = std::vector > class Stack_v2 
{
private:

	C < T > m_data;
};

//  ================================================================================================

template 
< 
	template < typename E > typename C1,
	template < typename E > typename C2, typename T 
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

template < typename T > struct Outer { template < typename U > struct Inner; };

template < typename T > 

template < typename U > struct Outer < T > ::Inner {};

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
	Stack_v1 < int > stack_v1_1;

	stack_v1_1.push(1); 
	
	assert(stack_v1_1.top() == 1); 
	
	stack_v1_1.pop();

//  ------------------------------------------------------------------------------------------------

	Stack_v1 < double, std::deque < double > > stack_v1_2;
	
	Stack_v2 < double, std::deque > stack_v2;

//  ------------------------------------------------------------------------------------------------

	std::vector < int > vector_1({ 1, 2, 3, 4, 5 });

	auto deque = copy < std::vector, std::deque > (vector_1);

//  ------------------------------------------------------------------------------------------------

	[[maybe_unused]] Pair pair(1, 1);

	std::vector vector_2({ 1, 2, 3, 4, 5 });

//  ------------------------------------------------------------------------------------------------

	[[maybe_unused]] typename Outer < int > ::template Inner < int > inner;

//  ------------------------------------------------------------------------------------------------

	using type_1 = int;

	using type_2 = std::string;

	using type_3 = double;

	Entity < type_1   , type_3   > ().test();
	Entity < type_2   , type_2   > ().test();
	Entity < type_2   , type_1   > ().test();
	Entity < type_1 * , type_2 * > ().test();
	Entity < type_1   , type_2   > ().test();

//	Entity < type_1   , type_1   > ().test(); // error
//	Entity < type_1 * , type_1 * > ().test(); // error
}