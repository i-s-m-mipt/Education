#include <ranges>
#include <sstream>
#include <string>
#include <vector>

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    for ([[maybe_unused]] auto element : std::ranges::views::iota(1, 5));

//  ------------------------------------------------------------------------------------

    std::stringstream stream("1 2 3 4 5 a");

//  ------------------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::ranges::views::istream < int > (stream));

//  ------------------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::ranges::views::split("1,2,3,4,5"s, ','));

//  ------------------------------------------------------------------------------------

    std::vector < int > vector = { 1, 2, 3, 4, 5 };

    auto lambda = [](auto x){ return x; };

//  ------------------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::ranges::views::transform(vector, lambda));
}