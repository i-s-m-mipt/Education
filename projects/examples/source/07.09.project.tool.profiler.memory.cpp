#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

/////////////////////////////////////////////////////////////////////////////////////

int main() // support: valgrind --leak-check=yes ./07.09.project.tool.profiler.memory
{
	auto array = new int[5]{ 1, 2, 3, 4, 5 };

	assert(array[1'000] == 0);

//  delete[] array; // bad

	std::cout << "main : enter char to continue : "; char c; std::cin >> c;
}