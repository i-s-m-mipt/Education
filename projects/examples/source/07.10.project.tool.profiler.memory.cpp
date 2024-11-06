#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

using namespace std::literals;

int main()
{
	auto size_1 = 5uz, size_2 = 1'000'000uz;

	for (auto i = 0uz; i < size_1; ++i)
	{
		auto array = new int[size_2]{};

		array[size_2] = 1;

		std::this_thread::sleep_for(2s);

//  	delete[] array; // bad
	}

	std::cout << "Enter any character to continue : "; char c; std::cin >> c;
}