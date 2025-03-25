#include <cassert>
#include <vector>
#include <utility>

///////////////////////////////////////////////////////////////////

template < typename T, typename C = std::vector < T > > class Stack
{
public :

	void push(T x)
	{
		m_container.push_back(std::move(x));
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
//		auto copy = top();
//
//		pop();
//		
//		return copy;
//	}

private :

	C m_container;
};

///////////////////////////////////////////////////////////////////

int main()
{
	Stack < int > stack;

//  --------------------------------
	
	stack.push(1);

//  --------------------------------

//	assert(stack.pop() == 1); // bad

	assert(stack.top() == 1);

//  --------------------------------
	
	stack.pop();
}