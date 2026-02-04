///////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling

///////////////////////////////////////////////////////////////////

// section : Exception Handling

///////////////////////////////////////////////////////////////////

// content : Container Stack
//
// content : Exception-Safe Interfaces

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

	void pop()
	{ 
		m_container.pop_back();
	}

//  ----------------------------------------

//	auto top_and_pop_v1() // error
//	{
//		auto x = top();
//
//		pop();
//		
//		return x;
//	}

//  ----------------------------------------

	auto top_and_pop_v2()
    {
        auto x = new T(top());

        pop();

        return x;
    }

//  ----------------------------------------

    void top_and_pop_v3(T & x)
    {
        x = top();

        pop();
    }

private :

	C m_container;
};

///////////////////////////////////////////////////////////////////

int main()
{
	Stack < int > stack;

//  -------------------------------------
	
	stack.push(1);

	stack.push(2);

	stack.push(3);

//  -------------------------------------

	assert(stack.top() == 3);

//  -------------------------------------
	
	stack.pop();

//  -------------------------------------

	int x = 0, * y = nullptr;

//  -------------------------------------

//	x = stack.top_and_pop_v1( ); // error

	y = stack.top_and_pop_v2( );

		stack.top_and_pop_v3(x);

//  -------------------------------------

	assert( x == 1);

	assert(*y == 2);

//  -------------------------------------

	delete y;
}

///////////////////////////////////////////////////////////////////