#include <cassert>
#include <iterator>
#include <string_view>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto view  = "1"sv;
        
    auto begin = std::begin(view), end = std::end(view);

    auto rule  = boost::spirit::x3::int_
    [
        ([](auto && context){ assert(boost::spirit::x3::_attr(context) == 1); })
    ];

    auto space = boost::spirit::x3::ascii::space;

//  ---------------------------------------------------------------------------------

    assert(boost::spirit::x3::phrase_parse(begin, end, rule, space) && begin == end);
}