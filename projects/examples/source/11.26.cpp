//////////////////////////////////////////////////////////////////////////////////////

// chapter : Programming with Algorithms

//////////////////////////////////////////////////////////////////////////////////////

// content : Views
//
// content : Lazy Evaluations
//
// content : View std::views::iota
//
// content : View std::views::istream
//
// content : View std::views::split
//
// content : View std::views::transform
//
// content : View std::views::all
//
// content : View std::views::take
//
// content : Function std::ranges::to
//
// content : User-Defined Views
//
// content : Base Class std::ranges::view_interface

//////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

//////////////////////////////////////////////////////////////////////////////////////

template < typename T > class View : public std::ranges::view_interface < View < T > >
{
public :

    View() = default;

//  -----------------------------------------------------------

    View(std::vector < T > const & vector)
    :
        m_begin(std::cbegin(vector)), m_end(std::cend(vector))
    {}

//  -----------------------------------------------------------

    auto begin() const { return m_begin; }

    auto end  () const { return m_end;   }

private :

    typename std::vector < T > ::const_iterator m_begin, m_end;
};

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    for ([[maybe_unused]] auto element : std::views::iota(1, 5));

//  ---------------------------------------------------------------------------

    std::stringstream stream("1 2 3 4 5 a");

//  ---------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::views::istream < int > (stream));

//  ---------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : std::views::split("1 2 3 4 5"s, ' '));

//  ---------------------------------------------------------------------------

    std::vector < int > vector = { 3, 2, 1, 4, 5 };

//  ---------------------------------------------------------------------------

    auto lambda = [](auto x) static { return x; };

//  ---------------------------------------------------------------------------

    auto view = std::views::transform(std::views::all(vector), lambda);

//  ---------------------------------------------------------------------------

    std::ranges::sort(std::views::take(vector, 3));

//  ---------------------------------------------------------------------------

    assert(vector == std::vector < int > ({ 1, 2, 3, 4, 5 }));

//  ---------------------------------------------------------------------------

    assert(std::ranges::to < std::vector < int > > (view) == vector);

//  ---------------------------------------------------------------------------

    for ([[maybe_unused]] auto element : View < int > (vector));
}

//////////////////////////////////////////////////////////////////////////////////////