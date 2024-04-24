#include <deque>
#include <iostream>
#include <iterator>
#include <vector>

// =================================================================================================

template < typename T, typename C = std::vector < T > > class Stack_v1
{
public: // note: member functions instantiated only if used, also called templated entities

	void push(T value);

	[[nodiscard]] T top() const;

	void pop();

	[[nodiscard]] std::size_t size() const { return std::size(m_container); }

private:

	C m_container; // note: internal storage

}; // template < typename T, typename C = std::vector < T > > class Stack_v1

// =================================================================================================

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

// =================================================================================================

template < typename T, template < typename E > typename C = std::vector > class Stack_v2 
{
public:

	[[nodiscard]] std::size_t size() const { return std::size(m_container); }

private:

	C < T > m_container;

}; // template < typename T, template < typename E > typename C = std::vector > class Stack_v2

// =================================================================================================

template < template < typename E > typename C1,
		   template < typename E > typename C2, typename T >
		   
[[nodiscard]] inline C2 < T > copy(const C1 < T > & container_in)
{
	return C2 < T > (std::cbegin(container_in), std::cend(container_in));
}

template < typename T1, typename T2 > struct Pair { T1 x{}; T2 y{}; }; // note: see std::pair

template < typename T > class Container { public: Container(std::size_t, const T &) {} }; 

// =================================================================================================

template < typename T > class Outer { public: template < typename U > class Inner; };

template < typename T > template < typename U > class Outer < T > ::Inner {}; // note: nested template

// =================================================================================================

template < typename T1, typename T2 > class C // note: basic template
{
public: void f() const { std::cout << "template < T1, T2 > C" << std::endl; }
};

template < typename T > class C < T, T > // note: partial specialization for T, T
{
public: void f() const { std::cout << "template < T > C < T, T > " << std::endl; }
};

template < typename T > class C < T, int > // note: partial specialization for T, int
{
public: void f() const { std::cout << "template < T > C < T, int > " << std::endl; }
};

template < typename T1, typename T2 > class C < T1*, T2* > // note: partial specialization for T1*, T2*
{
public: void f() const { std::cout << "template < T1, T2 > C < T1*, T2* > " << std::endl; }
};

template <> class C < int, double > // note: full specialization for int, double
{
public: void f() const { std::cout << "template <> C < int, double > " << std::endl; }
};

// =================================================================================================

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

	const std::vector < int > container_in { 1, 2, 3, 4, 5 };

	[[maybe_unused]] const auto container_out = copy < std::vector, std::deque > (container_in);

	Stack_v2 new_stack = deque_stack_v2;

	[[maybe_unused]] const Pair      pair     { 1, 42 }; // note: generated deduction guide for aggregate
	[[maybe_unused]] const Container container( 1, 42 ); // note: generated deduction guide for aggregate

	[[maybe_unused]] typename Outer < int > ::template Inner < int > object; // note: impressed?

	C < char,   double > ().f(); // note: basic template for T1, T2
	C < char,   char   > ().f(); // note: partial specialization for T, T
	C < double, int    > ().f(); // note: partial specialization for T, int
	C < int * , char * > ().f(); // note: partial specialization for T1*, T2*
	C < int,    double > ().f(); // note: full specialization for int, double

//	C < int,    int    > ().f(); // error: unresolved partial specialization
//	C < int * , int *  > ().f(); // error: unresolved partial specialization

	return 0;
}