#include <iostream>
#include <vector>
#include <stack>

template < typename T, typename C = std::vector < T > > class Stack
{
public:

	void push(T value)
	{
		m_container.push_back(std::move(value));
	}

	[[nodiscard]] T top() noexcept(noexcept(m_container.back()))
	{ 
		return m_container.back(); // note: undefined behavior if empty
	}

	void pop() noexcept(noexcept(m_container.pop_back()))
	{ 
		m_container.pop_back(); // note: undefined behavior if empty
	}

//	T pop() { ... } // bad: unsafe design

private:

	C m_container;

}; // template < typename T, typename C = std::vector < T > > class Stack

int main()
{
	Stack < int > stack; stack.push(42);

//	auto value = stack.pop(); // bad: possible problem here

	return 0;
}