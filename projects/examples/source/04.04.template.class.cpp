#include <cassert>
#include <deque>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

//  ================================================================================================

template < typename T, typename C = std::vector < T > > class Stack_v1
{
public:

	void push(T value);

	auto top() const;

	void pop();

	auto size() const 
	{ 
		return std::size(m_data); 
	}

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
public:

	void push(T value)
	{
		m_data.push_back(std::move(value));
	}

	auto top() const
	{
		return m_data.back();
	}

	void pop()
	{
		m_data.pop_back();
	}

	auto size() const
	{ 
		return std::size(m_data); 
	}

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
	return C2 < T > (std::cbegin(container), std::cend(container));
}

//  ================================================================================================

template < typename T1, typename T2 > struct Pair 
{ 
	T1 x = T1(); 
	T2 y = T2(); 
};

//  ================================================================================================

template < typename T > struct Outer { template < typename U > struct Inner; };

template < typename T > 

template < typename U > struct Outer < T > ::Inner {};

//  ================================================================================================

template < typename T1, typename T2 > struct Entity
{
	void test() const
	{ 
		std::clog << "Entity::test (1)\n"; 
	}
};

template < typename T > struct Entity < T, T >
{
	void test() const 
	{ 
		std::clog << "Entity::test (2)\n"; 
	}
};

template < typename T > struct Entity < T, int >
{
	void test() const 
	{ 
		std::clog << "Entity::test (3)\n"; 
	}
};

template < typename T1, typename T2 > struct Entity < T1 * , T2 * >
{
	void test() const 
	{ 
		std::clog << "Entity::test (4)\n"; 
	}
};

template <> struct Entity < int, std::string >
{
	void test() const 
	{ 
		std::clog << "Entity::test (5)\n"; 
	}
};

//  ================================================================================================

int main()
{
	Stack_v1 < int > stack;

	stack.push(1);
	stack.push(2);
	stack.push(3);

	assert(stack.size() == 3 && stack.top() == 3);

	stack.pop();

	assert(stack.size() == 2 && stack.top() == 2);

//  ------------------------------------------------------------------------------------------------

	Stack_v1 < double, std::deque < double > > deque_stack_v1;
	Stack_v2 < double, std::deque            > deque_stack_v2;

//  ------------------------------------------------------------------------------------------------

	std::vector < int > vector_1 { 1, 2, 3, 4, 5 };

	auto deque = copy < std::vector, std::deque > (vector_1);

//  ------------------------------------------------------------------------------------------------

	Stack_v2 new_stack = deque_stack_v2;

	[[maybe_unused]] Pair pair { 1, 2 };

	std::vector vector_2 { 1, 2, 3, 4, 5 };

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