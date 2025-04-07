///////////////////////////////////////////////////////////////////

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

//  ----------------------------------------

	auto top() const
	{ 
		return m_container.back();
	}

//  ----------------------------------------

	void pop_v1()
	{ 
		m_container.pop_back();
	}

//  ----------------------------------------

//	auto pop_v2() // bad
//	{
//		auto copy = top();
//
//	//  ------------------
//
//		pop_v1();
//
//	//  ------------------
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

//  -----------------------------------
	
	stack.push(1);

	stack.push(2);

//  -----------------------------------

	assert(stack.top() == 2);

//  -----------------------------------
	
	stack.pop_v1();

//  -----------------------------------

//	assert(stack.pop_v2() == 1); // bad
}

///////////////////////////////////////////////////////////////////