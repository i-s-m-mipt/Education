#include <cassert>
#include <iterator>
#include <string_view>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto view  = "1"sv;
        
    auto begin = std::begin(view), end = std::end(view);

    auto rule  = boost::spirit::x3::int_;

    auto space = boost::spirit::x3::ascii::space;

    auto x = 0;

//  ------------------------------------------------------------------------------------

    assert(boost::spirit::x3::phrase_parse(begin, end, rule, space, x) && begin == end);

    assert(x == 1);
}