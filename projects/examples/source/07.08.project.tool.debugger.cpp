#include <cassert>
#include <numeric>
#include <vector>

//  ================================================================================================

[[nodiscard]] constexpr bool binary_search(const std::vector < int > & vector, int key) noexcept
{
	std::size_t l = 0, r = std::size(vector);

	if (r == 0) return false;

	if (r == 1) return (vector[0] == key);

	while (l < r)
	{
		const auto m = std::midpoint(l, r); vector[m] < key ? l = m + 1 : r = m;
	}

	return (vector[l] == key);
}

//  ================================================================================================

int main()
{
	assert(binary_search({1, 3, 4, 5, 6, 7, 8 }, 7));

	return 0;
}