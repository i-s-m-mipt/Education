#include <iostream>
#include <ranges>
#include <string>
#include <vector>

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    for ([[maybe_unused]] auto element : std::ranges::views::iota(1, 5));

//  -------------------------------------------------------------------------------------

    std::cout << "main : enter ints and non-int : ";

//  -------------------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::ranges::views::istream < int > (std::cin));

//  -------------------------------------------------------------------------------------

    auto string = "1,2,3,4,5"s;

//  -------------------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::ranges::views::split(string, ','));

//  -------------------------------------------------------------------------------------

    std::vector < int > vector = { 1, 2, 3, 4, 5 };

    auto lambda = [](auto x){ return x; };

//  -------------------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::ranges::views::transform(vector, lambda));
}