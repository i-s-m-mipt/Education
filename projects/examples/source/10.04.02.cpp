#include <functional>
#include <string>
#include <tuple>

///////////////////////////////////////////////////////

auto hash(const std::string & string)
{
	auto seed = 0uz;

	for (auto element : string) 
	{
		(seed *= 31) += element;
	}

	return seed;
}

///////////////////////////////////////////////////////

int main()
{
	auto string = "aaaaa";

//  ---------------------------------------------------

	std::ignore = hash(string);

	std::ignore = std::hash < std::string > ()(string);
}