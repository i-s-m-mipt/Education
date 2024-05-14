#include <iostream>
#include <vector>
#include <stack>

//  ================================================================================================

template < typename T, typename C = std::vector < T > > class Stack
{
public:

	constexpr void push(T value)
	{
		m_container.push_back(std::move(value));
	}

	[[nodiscard]] constexpr T top() const noexcept
	{ 
		return m_container.back();
	}

	constexpr void pop() noexcept
	{ 
		m_container.pop_back();
	}

//	[[nodiscard]] constexpr T pop() { ... } // bad

	[[nodiscard]] constexpr std::size_t size() const noexcept
	{ 
		return m_container.size(); 
	}

private:

	C m_container;

}; // template < typename T, typename C = std::vector < T > > class Stack

//  ================================================================================================

int main()
{
	Stack < int > stack; 
	
	stack.push(42);

//	auto value = stack.pop(); // bad

	return 0;
}