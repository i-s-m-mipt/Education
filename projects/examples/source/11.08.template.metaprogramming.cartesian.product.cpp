#include <concepts>
#include <iostream>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

// =================================================================================================

[[nodiscard]] constexpr bool increase(std::vector < std::size_t > & steps,
								const std::vector < std::size_t > & sizes) noexcept
{
	auto is_increased = false;

	for (int i = static_cast < int > (std::size(steps)) - 1; i >= 0; --i)
	{
		if (steps[i]++; steps[i] == sizes[i])
		{
			steps[i] = 0;
		}
		else
		{
			is_increased = true; break;
		}
	}

	return is_increased;
}

// =================================================================================================

template < typename F, std::size_t ... Is > constexpr void apply(F && f, 
	const std::integer_sequence < std::size_t, Is ... > , 
	const std::vector           < std::size_t         > & steps, const auto & tuple)
{
	f(*(std::next((std::get < Is > (tuple)).first, steps[Is]))...);
}

// =================================================================================================

template < std::forward_iterator ... Ts > [[nodiscard]] constexpr auto combine(std::pair < Ts, Ts > ... args)
{
	std::vector < std::tuple < typename std::iterator_traits < Ts > ::value_type ... > > result;

	const auto push = [&result](auto && ... args){ result.emplace_back(args...); };
	
	std::vector steps (sizeof...(args), std::size_t(0));

	std::vector sizes = { static_cast < std::size_t > (std::distance(args.first , args.second))... };

	do
	{
		apply(push, std::make_index_sequence < sizeof...(args) > (), steps, std::tie(args...));
	} 
	while (increase(steps, sizes));

	return result;
}

// =================================================================================================

int main()
{
    std::vector vector_1 = { 'a', 'b', 'c' }; // note: different homogeneous containers
	std::vector vector_2 = { 100, 200, 300 };
	std::vector vector_3 = { 1.0, 2.0, 3.0 };

	const auto cartesian_product = combine(
		std::make_pair(std::begin(vector_1), std::end(vector_1)),
		std::make_pair(std::begin(vector_2), std::end(vector_2)),
		std::make_pair(std::begin(vector_3), std::end(vector_3)));

	for (const auto & [x, y, z] : cartesian_product)
	{
		std::cout << "{ " << x << ", " << y << ", " << z << " }" << std::endl;
	}

	return 0;
}