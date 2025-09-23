///////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V > auto make_vector(V view) 
{
    std::vector < std::ranges::range_value_t < V > > vector;

    if constexpr (std::ranges::sized_range < V > )
    {
        vector.reserve(std::ranges::size(view));
    }

    std::ranges::copy(view, std::back_inserter(vector));

    return vector;
}

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    for ([[maybe_unused]] auto element : std::ranges::views::iota(1, 5));

//  -----------------------------------------------------------------------------------

    std::stringstream stream("1 2 3 4 5 a");

//  -----------------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::ranges::views::istream < int > (stream));

//  -----------------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::ranges::views::split("1,2,3,4,5"s, ','));

//  -----------------------------------------------------------------------------------

    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------------------------------

    auto lambda = [](auto x){ return x; };

//  -----------------------------------------------------------------------------------

    auto view = std::ranges::views::transform(std::ranges::views::all(vector), lambda);

//  -----------------------------------------------------------------------------------

    assert(make_vector(view) == std::vector < int > ({ 1, 2, 3, 4, 5 }));
}

///////////////////////////////////////////////////////////////////////////////////////