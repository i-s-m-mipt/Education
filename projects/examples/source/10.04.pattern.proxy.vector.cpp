#include <cassert>
#include <memory>
#include <vector>

class Loader // note: proxy class with lazy loading
{
public:

	void load() 
	{
		if (!m_data) m_data = std::make_unique < int > (42);
	}

	std::unique_ptr < int > m_data; // note: nullptr

}; // class Loader

int main()
{
	constexpr std::size_t size = 64;

	constexpr bool array[size]{};

	assert(sizeof(array) == size);

	std::vector < bool > vector(size); // good: 1 bit per bool

	constexpr std::size_t middle = size / 2;

	vector[middle] = true;

	[[maybe_unused]] const auto value = vector[middle]; // note: auto -> std::vector < bool > ::reference
	
	return 0;
}