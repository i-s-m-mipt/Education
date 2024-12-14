#include <vector>
#include <utility>

//  ================================================================================================

template < typename T, typename C = std::vector < T > > class Stack
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

//	auto pop() // bad
//	{
//		auto copy = top(); pop(); return copy;
//	}

	auto size() const
	{ 
		return std::size(m_data); 
	}

private:

	C m_data;
};

//  ================================================================================================

int main()
{
	Stack < int > stack; 
	
	stack.push(1);

	std::ignore = stack.top(); stack.pop();

//	std::ignore = stack.pop(); // bad
}