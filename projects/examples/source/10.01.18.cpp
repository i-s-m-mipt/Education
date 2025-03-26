#include <cassert>
#include <queue>

///////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/QueueArray.html

///////////////////////////////////////////////////////////////////

int main()
{
	std::queue < int > queue;

//  ------------------------------------------------

	queue.push(1);
		
	queue.push(2);

//  ------------------------------------------------

	assert(queue.front() == 1 && queue.back() == 2);

//  ------------------------------------------------

    queue.push(3);

	queue.pop ( );

//  ------------------------------------------------

	assert(queue.front() == 2 && queue.back() == 3);
}