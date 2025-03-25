#include <cassert>
#include <iterator>
#include <string_view>
#include <utility>

using namespace std::literals;

#include <boost/fusion/include/std_pair.hpp>

#include <boost/spirit/home/x3.hpp>

////////////////////////////////////////////////////////////////////

int main()
{
    auto view  = "1 1"sv;
        
    auto begin = std::begin(view), end = std::end(view);

    auto rule  = boost::spirit::x3::int_ >> boost::spirit::x3::int_;

    auto space = boost::spirit::x3::ascii::space;

    std::pair < int, int > pair;

//  ----------------------------------------------------------------

    boost::spirit::x3::phrase_parse(begin, end, rule, space, pair);

//  ----------------------------------------------------------------

    assert(pair == std::make_pair(1, 1));
}