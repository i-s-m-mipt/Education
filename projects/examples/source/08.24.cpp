///////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Applied Computations

///////////////////////////////////////////////////////////////////////////////////////////////

// content : Random Numbers
//
// content : Seeds, Engines and Distributions
//
// content : Non-Deterministic Pseudo-Random Entropy Sources
//
// content : Engine std::random_device
//
// content : Engine std::mt19937_64
//
// content : Distribution std::normal_distribution
//
// content : Function std::floor

///////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <cstddef>
#include <print>
#include <random>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::normal_distribution distribution(25.0, 8.0);

//  -------------------------------------------------------------------------------------------

	std::random_device device;

//  -------------------------------------------------------------------------------------------

	std::mt19937_64 engine(device());

//  -------------------------------------------------------------------------------------------

	auto size = 50uz;

//  -------------------------------------------------------------------------------------------

	std::vector < std::size_t > vector(size, 0);

//  -------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < 1 << 20; ++i)
	{
		if (auto x = distribution(engine); x > 0 && x < size)
		{
			++vector[static_cast < std::size_t > (std::floor(x))];
		}
	}

//  -------------------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		std::print("main : vector[{:0>2}] : {}\n", i, std::string(vector[i] / (1 << 10), '+'));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////