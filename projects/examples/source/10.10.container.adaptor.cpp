#include <cassert>
#include <iterator>
#include <queue>
#include <stack>

int main()
{
	std::stack < int > stack; // support: LIFO

	stack.push(1);
	stack.push(2);
	stack.push(3);

	assert(std::size(stack) == 3);

	assert(stack.top() == 3);

	stack.pop();

	assert(stack.top() == 2);

//  ================================================================================================

	std::queue < int > queue; // support: FIFO

	queue.push(1);
	queue.push(2);
	queue.push(3);

	assert(std::size(queue) == 3);

	assert(queue.front() == 1); assert(queue.back() == 3);

	queue.pop();

	assert(queue.front() == 2); assert(queue.back() == 3);

//  ================================================================================================

	std::priority_queue < int > priority_queue; // support: FIFO+

	priority_queue.push(2);
	priority_queue.push(3);
	priority_queue.push(1);

	assert(std::size(priority_queue) == 3);

	assert(priority_queue.top() == 3);

	priority_queue.pop();

	assert(priority_queue.top() == 2);

	return 0;
}