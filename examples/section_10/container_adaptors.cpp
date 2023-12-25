#include <cassert>
#include <queue>
#include <stack>

int main()
{
	std::stack < int > s; // note: LIFO concept

	s.push(1);
	s.push(2);
	s.push(3);

	assert(std::size(s) == 3);

	assert(s.top() == 3);

	s.pop();

	assert(s.top() == 2);

	std::queue < int > q; // note: FIFO concept

	q.push(1);
	q.push(2);
	q.push(3);

	assert(std::size(q) == 3);

	assert(q.front() == 1); assert(q.back() == 3);

	q.pop();

	assert(q.front() == 2); assert(q.back() == 3);

	return 0;
}