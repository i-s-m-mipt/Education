//////////////////////////////////////////////

#include <vector>

//////////////////////////////////////////////

int main()
{
    auto size = 5uz;

//  ------------------------------------------

	std::vector < std::vector < int > > vector
	(
		size, std::vector < int > (size, 0)
	);

//  ------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			vector[i][j] = j + 1;
		}
	}
}

//////////////////////////////////////////////