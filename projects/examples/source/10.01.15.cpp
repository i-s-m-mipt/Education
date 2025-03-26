#include <cassert>
#include <stack>

///////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/StackArray.html

///////////////////////////////////////////////////////////////////

int main()
{
	std::stack < int > stack;

//  -------------------------

	stack.push(1);

	stack.push(2);

//  -------------------------

	assert(stack.top() == 2);

//  -------------------------
    
    stack.pop();

//  -------------------------

	assert(stack.top() == 1);
}