#include <iostream>
#include <vector>
#include <stack>

template < typename T, typename Container = std::vector < T > > class Stack
{
public:

	[[nodiscard]]       T & top()       noexcept(noexcept(m_container.back()))
	{ 
		return m_container.back(); // note: undefined behavior if empty
	}

	[[nodiscard]] const T & top() const noexcept(noexcept(m_container.back()))
	{
		return m_container.back(); // note: undefined behavior if empty
	}

	void push(T value) 
	{
		m_container.push_back(std::move(value));
	}

	void pop() noexcept(noexcept(m_container.pop_back()))
	{ 
		m_container.pop_back(); // note: undefined behavior if empty
	}

//	T pop() { ... } // bad: unsafe design

private:

	Container m_container;

}; // template < typename T, typename Container = std::vector < T > > class Stack

int main()
{
	Stack < int > stack; stack.push(42);

//	auto value = stack.pop(); // bad: possible problem here

	return 0;
}