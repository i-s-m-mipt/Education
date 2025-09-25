////////////////////////////////////////////////////////

#include <functional>
#include <string>
#include <tuple>

////////////////////////////////////////////////////////

auto hash(std::string const & string)
{
	auto seed = 0uz;

	for (auto element : string) 
	{
		(seed *= 31) += element;
	}

	return seed;
}

////////////////////////////////////////////////////////

int main()
{
	std::ignore = hash("aaaaa");

//  ----------------------------------------------------

	std::ignore = std::hash < std::string > ()("aaaaa");
}

////////////////////////////////////////////////////////