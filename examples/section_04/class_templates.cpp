#include <iostream>

template < typename T, auto N >
class Stack
{
public:

	using size_t = decltype(N);

public:

	T top() const;

	void pop();

	void push(T value);

public:

	auto size() const { return m_size; }

private:

	T m_array[N]{};
	size_t m_size = 0;

}; // class Stack

template < typename T, auto N >
T Stack < T, N > ::top() const
{
	return (m_size == 0 ? T() : m_array[m_size - 1]); // note: no errors handling
}

template < typename T, auto N >
void Stack < T, N > ::pop()
{
	if (m_size > 0) --m_size; // note: no errors handling
}

template < typename T, auto N >
void Stack < T, N > ::push(T value)
{
	if (m_size < N) m_array[m_size++] = value; // note: no errors handling
}

template < typename T1, typename T2 >
struct Pair
{
	T1 first {};
	T2 second{};

}; // struct Pair

template < typename T >
class Container
{
public:

	Container([[maybe_unused]] int count, [[maybe_unused]] const T & value) {}

}; // class Container

template < typename T1, typename T2 >
class C // note: basic template
{
public:

	void f() const
	{
		std::cout << "template for T1, T2" << std::endl;
	}

}; // class C

template < typename T >
class C < T, T > // note: partial specialization for T, T
{
public:

	void f() const
	{
		std::cout << "partial specialization for T, T" << std::endl;
	}

}; // class C < T, T >

template < typename T >
class C < T, int > // note: partial specialization for T, int
{
public:

	void f() const
	{
		std::cout << "partial specialization for T, int" << std::endl;
	}

}; // class C < T, int >

template < typename T1, typename T2 >
class C < T1*, T2* > // note: partial specialization for T1*, T2*
{
public:

	void f() const
	{
		std::cout << "partial specialization for T1*, T2*" << std::endl;
	}

}; // class C < T1*, T2* >

template <>
class C < int, double > // note: full specialization for int, double
{
public:

	void f() const
	{
		std::cout << "full specialization for int, double" << std::endl;
	}

}; // class C < int, double >

int main()
{
	Stack < int, 10 > stack;

	stack.push(1);
	stack.push(2);
	stack.push(3);

	stack.pop();

	std::cout << stack.top() << std::endl;

	[[maybe_unused]] Stack new_stack = stack;

	[[maybe_unused]] Pair p{ 1.0, 100 }; // note: generated deduction guide for aggregate

	[[maybe_unused]] Container c(10, 1.0); // note: generated deduction guide for aggregate

	C < char,   double > ().f(); // note: template for T1, T2
	C < char,   char   > ().f(); // note: partial specialization for T, T
	C < double, int    > ().f(); // note: partial specialization for T, int
	C < int * , char * > ().f(); // note: partial specialization for T1*, T2*
	C < int,    double > ().f(); // note: full specialization for int, double

//	C < int,    int    > ().f(); // error: unresolved partial specialization
//	C < int * , int *  > ().f(); // error: unresolved partial specialization

	return 0;
}