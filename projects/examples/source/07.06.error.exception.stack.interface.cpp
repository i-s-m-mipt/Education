#include <vector>
#include <utility>

//  ================================================================================================

template < typename T, typename C = std::vector < T > > class Stack
{
public:

	void push(T data)
	{
		m_container.push_back(std::move(data));
	}

	auto top() const
	{ 
		return m_container.back();
	}

	void pop()
	{ 
		m_container.pop_back();
	}

//	auto pop() // bad
//	{
//		auto copy = top(); pop(); return copy;
//	}

private:

	C m_container;
};

//  ================================================================================================

int main()
{
	Stack < int > stack; 
	
	stack.push(1);

//	std::ignore = stack.pop(); // bad

	std::ignore = stack.top(); stack.pop();
}