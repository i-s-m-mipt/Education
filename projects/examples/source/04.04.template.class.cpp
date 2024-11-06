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

	[[nodiscard]] auto top() const;

	void pop();

	[[nodiscard]] auto size() const 
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

template < typename T, typename C > [[nodiscard]] auto Stack_v1 < T, C > ::top() const
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

	[[nodiscard]] auto top() const
	{
		return m_data.back();
	}

	void pop()
	{
		m_data.pop_back();
	}

	[[nodiscard]] auto size() const
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
[[nodiscard]] auto copy(const C1 < T > & container_from)
{
	return C2 < T > (std::cbegin(container_from), std::cend(container_from));
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

	assert(stack.top() == 3);

	stack.pop();

	assert(stack.top() == 2);

//  ------------------------------------------------------------------------------------------------

	Stack_v1 < double, std::deque < double > > deque_stack_v1;
	Stack_v2 < double, std::deque            > deque_stack_v2;

//  ------------------------------------------------------------------------------------------------

	std::vector < int > container_from({ 1, 2, 3, 4, 5 });

	auto deque = copy < std::vector, std::deque > (container_from);

	assert(deque == std::deque < int > ({ 1, 2, 3, 4, 5 }));

//  ------------------------------------------------------------------------------------------------

	Stack_v2 new_stack = deque_stack_v2;

	[[maybe_unused]] Pair pair = { 1, 2 };

	std::vector vector(5, 0);

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