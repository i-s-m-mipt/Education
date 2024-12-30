#include <cassert>
#include <complex>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string_view>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

//  ================================================================================================

auto parse(std::string_view data)
{
    auto begin = std::begin(data), end = std::end(data);

    auto x = 0.0, y = 0.0;

    using boost::spirit::x3::_attr;

    auto set_x = [&x](auto && context){ x = _attr(context); };
    auto set_y = [&y](auto && context){ y = _attr(context); };

    using boost::spirit::x3::double_;

    auto rule = 
    (
        '(' >> double_[set_x] >> ',' >> double_[set_y] >> ')' |
        '(' >> double_[set_x]                          >> ')' |
               double_[set_x]
    );

    auto skip = boost::spirit::x3::ascii::space;

    auto result = boost::spirit::x3::phrase_parse(begin, end, rule, skip);

    if (!result || begin != end)
    {
        throw std::runtime_error("invalid data");
    }
    
    return std::complex < double > (x, y);
}

//  ================================================================================================

int main()
{
    assert(parse("(1.0, 2.0)") == 1.0 + 2.0i);
    assert(parse("(1.0     )") == 1.0 + 0.0i);
    assert(parse(" 1.0      ") == 1.0 + 0.0i);
}