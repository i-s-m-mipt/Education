#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <mutex>

std::deque < int > deque;
std::mutex		   mutex;

void add(int value)
{
	std::lock_guard < std::mutex > lock(mutex);
	deque.push_back(value);
}

bool find(int value)
{
	std::lock_guard < std::mutex > lock(mutex);
	return std::find(deque.begin(), deque.end(), value) != deque.end();
}

int main(int argc, char ** argv)
{
	add(42);

	std::cout << std::boolalpha << find(1) << " " << find(42) << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}
