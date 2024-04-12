#include <iostream>
#include <iomanip>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <array>
#include <deque>
#include <algorithm>

template < std::size_t N >
bool increase(
	const std::array < std::size_t, N > & sizes,
		  std::array < std::size_t, N > & indexes)
{
	bool is_increased = false;

	for (std::size_t i = 0; i < N; ++i)
	{
		const std::size_t index = N - 1 - i;

		++indexes[index];

		if (indexes[index] >= sizes[index])
		{
			indexes[index] = 0;
		}
		else
		{
			is_increased = true;
			break;
		}
	}

	return is_increased;
}

template < typename F, std::size_t ... Indexes, std::size_t N, typename Tuple >
constexpr void apply(F && function, std::index_sequence < Indexes ... > ,
	const std::array < std::size_t, N > & indexes, const Tuple & tuple)
{
	function((*((std::get < Indexes > (tuple)).first + indexes[Indexes]))...);
}

template < typename ... Ts > [[nodiscard]] constexpr auto combine(std::pair < Ts, Ts > ... sequences)
{
    
	std::vector < std::tuple < typename std::iterator_traits < Ts > ::value_type ... > > result;
	
	constexpr auto size = sizeof...(Ts);

	std::array < std::size_t, size > sizes = { static_cast < std::size_t > (
		std::distance(sequences.first, sequences.second))... };

	std::array < std::size_t, size > indexes{};

	do
	{
		apply([&result](const auto & ... args) { result.emplace_back(args...); },
			std::make_index_sequence < size > (), indexes, std::tie(sequences...));
	} 
	while (increase(sizes, indexes));

	return result;
}

int main()
{
    std::vector vector_1 = { 'a', 'b', 'c' }; // note: different homogeneous collections
	std::vector vector_2 = { 100, 200, 300 };
	std::vector vector_3 = { 1.0, 2.0, 3.0 };

	const auto cartesian_product = combine(
		std::make_pair(std::begin(vector_1), std::end(vector_1)),
		std::make_pair(std::begin(vector_2), std::end(vector_2)),
		std::make_pair(std::begin(vector_3), std::end(vector_3))); // note: variadic

	for (const auto & [x, y, z] : cartesian_product)
	{
		std::cout << "{ " << x << ", " << y << ", " << z << " }" << std::endl;
	}

	return 0;
}