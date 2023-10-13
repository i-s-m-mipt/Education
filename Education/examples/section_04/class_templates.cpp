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
class X // note: basic template
{
public:

	void f() const
	{
		std::cout << "template for T1, T2" << std::endl;
	}

}; // class X

template < typename T >
class X < T, T > // note: partial specialization for T, T
{
public:

	void f() const
	{
		std::cout << "partial specialization for T, T" << std::endl;
	}

}; // class X < T, T >

template < typename T >
class X < T, int > // note: partial specialization for T, int
{
public:

	void f() const
	{
		std::cout << "partial specialization for T, int" << std::endl;
	}

}; // class X < T, int >

template < typename T1, typename T2 >
class X < T1*, T2* > // note: partial specialization for T1*, T2*
{
public:

	void f() const
	{
		std::cout << "partial specialization for T1*, T2*" << std::endl;
	}

}; // class X < T1*, T2* >

template <>
class X < int, double > // note: full specialization for int, double
{
public:

	void f() const
	{
		std::cout << "full specialization for int, double" << std::endl;
	}

}; // class X < int, double >

int main()
{
	Stack < int, 10 > stack;

	stack.push(1);
	stack.push(2);
	stack.push(3);

	stack.pop();

	std::cout << stack.top() << std::endl;

	Stack new_stack = stack;

	X < char,   double > ().f(); // note: template for T1, T2
	X < char,   char   > ().f(); // note: partial specialization for T, T
	X < double, int    > ().f(); // note: partial specialization for T, int
	X < int * , char * > ().f(); // note: partial specialization for T1*, T2*
	X < int,    double > ().f(); // note: full specialization for int, double

//	X < int,    int    > ().f(); // error: unresolved partial specialization
//	X < int * , int *  > ().f(); // error: unresolved partial specialization

	return 0;
}