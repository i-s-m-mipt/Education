#include <cassert>
#include <iterator>
#include <string_view>
#include <tuple>

using namespace std::literals;

#include <boost/fusion/include/std_tuple.hpp>

#include <boost/spirit/home/x3.hpp>

//////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto view  = "{ 1 1 }"sv;
        
    auto begin = std::begin(view), end = std::end(view);

    auto rule  = '{' >> boost::spirit::x3::int_ >> boost::spirit::x3::int_ >> '}';

    auto space = boost::spirit::x3::ascii::space;

    std::tuple < int, int > tuple;

//  ------------------------------------------------------------------------------

    boost::spirit::x3::phrase_parse(begin, end, rule, space, tuple);

//  ------------------------------------------------------------------------------

    assert(tuple == std::make_tuple(1, 1));
}