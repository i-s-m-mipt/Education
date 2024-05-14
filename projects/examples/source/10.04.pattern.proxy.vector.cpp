#include <cassert>
#include <memory>
#include <vector>

//  ================================================================================================

class Lazy_Loader
{
public:

	void lazy_load() 
	{
		if (!m_data) m_data = std::make_unique < int > (42);
	}

private:

	std::unique_ptr < int > m_data;

}; // class Lazy_Loader

//  ================================================================================================

int main()
{
	constexpr std::size_t size = 64;

	constexpr bool array[size]{};

	assert(sizeof(array) == size);

	std::vector < bool > vector(size); 

	constexpr std::size_t middle = size / 2;

	vector[middle] = true;
 
	[[maybe_unused]] const auto value = vector[middle]; // support: Proxy
	
	return 0;
}