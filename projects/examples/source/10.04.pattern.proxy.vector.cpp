#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

//  ================================================================================================

class Entity
{
public:

	void make_data() 
	{
		if (m_data == nullptr) 
		{
			m_data = std::make_unique < int > (1);
		}
	}

private:

	std::unique_ptr < int > m_data;
};

//  ================================================================================================

int main()
{
	bool array[5]{};

	assert(sizeof(array) == std::size(array));

	std::vector < bool > vector(1'000'000'000, false); 

	vector.front() = true;
 
	auto proxy = vector.front();

	assert(static_cast < bool > (proxy) == true);

	std::cout << "main : enter any character to continue : "; char c; std::cin >> c;
}