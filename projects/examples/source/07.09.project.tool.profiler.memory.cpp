#include <chrono>
#include <iostream>
#include <thread>

/////////////////////////////////////////////////////////////////////////////////////

int main() // support: valgrind --leak-check=yes ./07.09.project.tool.profiler.memory
{
	auto size = 5uz;

	auto array = new int[size]{};

	array[size] = 1;

//  delete[] array; // bad

	std::cout << "main : enter char to continue : "; char c; std::cin >> c;
}