#include <deque>
#include <iostream>
#include <vector>

template < typename T, typename C = std::vector < T > > class Stack_v1
{
public: // note: member functions instantiated only if used

	void push(T value);

	[[nodiscard]] T top() const;

	void pop();

	auto size() const { return m_container.size(); }

private:

	C m_container; // note: internal storage

}; // template < typename T, typename C = std::vector < T > > class Stack_v1

template < typename T, typename C > void Stack_v1 < T, C > ::push(T value)
{
	m_container.push_back(std::move(value));
}

template < typename T, typename C > [[nodiscard]] T Stack_v1 < T, C > ::top() const
{
	return m_container.back(); // note: undefined behavior if empty
}

template < typename T, typename C > void Stack_v1 < T, C > ::pop()
{
	m_container.pop_back(); // note: undefined behavior if empty
}

template < typename T, template < typename E > typename C = std::vector > class Stack_v2
{
public:

	auto size() const { return m_container.size(); }

private:

	C < T > m_container;

}; // template < typename T, template < typename E > typename C = std::vector > class Stack_v2

template < typename T1, typename T2 > struct Pair // note: see std::pair
{
	T1 x{};
	T2 y{};

}; // template < typename T1, typename T2 > struct Pair

template < typename T > class Container
{
public:

	Container([[maybe_unused]] int count, [[maybe_unused]] const T & value) {}

}; // template < typename T > class Container

template < typename T1, typename T2 > class C // note: basic template
{
public:

	void f() const
	{
		std::cout << "template for T1, T2" << std::endl;
	}

}; // template < typename T1, typename T2 > class C

template < typename T > class C < T, T > // note: partial specialization for T, T
{
public:

	void f() const
	{
		std::cout << "partial specialization for T, T" << std::endl;
	}

}; // template < typename T > class C < T, T >

template < typename T > class C < T, int > // note: partial specialization for T, int
{
public:

	void f() const
	{
		std::cout << "partial specialization for T, int" << std::endl;
	}

}; // template < typename T > class C < T, int >

template < typename T1, typename T2 > class C < T1*, T2* > // note: partial specialization for T1*, T2*
{
public:

	void f() const
	{
		std::cout << "partial specialization for T1*, T2*" << std::endl;
	}

}; // template < typename T1, typename T2 > class C < T1*, T2* >

template <> class C < int, double > // note: full specialization for int, double
{
public:

	void f() const
	{
		std::cout << "full specialization for int, double" << std::endl;
	}

}; // template <> class C < int, double >

int main()
{
	Stack_v1 < double, std::deque < double > > deque_stack_v1;

	Stack_v1 < int > stack; // note: std::vector is used by default as an internal storage

	stack.push(1);
	stack.push(2);
	stack.push(3);

	std::cout << stack.top() << std::endl;

	stack.pop();

	std::cout << stack.top() << std::endl;

	Stack_v2 < double, std::deque > deque_stack_v2; // good: no duplication

	Stack_v2 new_stack = deque_stack_v2;

	Pair p{ 1.0, 100 }; // note: generated deduction guide for aggregate

	Container c(10, 1.0); // note: generated deduction guide for aggregate

	C < char,   double > ().f(); // note: basic template for T1, T2
	C < char,   char   > ().f(); // note: partial specialization for T, T
	C < double, int    > ().f(); // note: partial specialization for T, int
	C < int * , char * > ().f(); // note: partial specialization for T1*, T2*
	C < int,    double > ().f(); // note: full specialization for int, double

//	C < int,    int    > ().f(); // error: unresolved partial specialization
//	C < int * , int *  > ().f(); // error: unresolved partial specialization

	return 0;
}