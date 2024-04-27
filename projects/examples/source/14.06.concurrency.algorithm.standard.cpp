#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char ** argv)
{
	std::vector < double > v(10'000'007, 0.5);

	{
		auto t1 = std::chrono::high_resolution_clock::now();

		double result = std::accumulate(v.begin(), v.end(), 0.0);

		auto t2 = std::chrono::high_resolution_clock::now();

		std::cout << std::setw(16) << std::left << std::fixed << "std::accumulate " << result <<
			" took " << std::chrono::duration_cast < std::chrono::milliseconds > (t2 - t1).count() << " (ms)\n";
	}

	{
		auto t1 = std::chrono::high_resolution_clock::now();

		double result = std::reduce(std::execution::par, v.begin(), v.end());

		auto t2 = std::chrono::high_resolution_clock::now();

		std::cout << std::setw(16) << std::left << std::fixed << "std::reduce " << result << 
			" took " << std::chrono::duration_cast <std::chrono::milliseconds> (t2 - t1).count() << " (ms)\n";
	}

	system("pause");

	return EXIT_SUCCESS;
}