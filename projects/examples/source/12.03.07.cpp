#include <cassert>
#include <complex>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string_view>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

//////////////////////////////////////////////////////////////////////////

auto parse(std::string_view view)
{
    auto begin = std::begin(view), end = std::end(view);

    auto x = 0.0, y = 0.0;

    using boost::spirit::x3::_attr;

    auto lambda_1 = [&x](auto && context){ x = _attr(context); };

    auto lambda_2 = [&y](auto && context){ y = _attr(context); };

    using boost::spirit::x3::double_;

    auto rule = 
    (
        '(' >> double_[lambda_1] >> ',' >> double_[lambda_2] >> ')' |

        '(' >> double_[lambda_1]                             >> ')' |
        
               double_[lambda_1]
    );

    auto space = boost::spirit::x3::ascii::space;

    auto state = boost::spirit::x3::phrase_parse(begin, end, rule, space);

    if (!state || begin != end)
    {
        throw std::runtime_error("invalid view");
    }
    
    return std::complex < double > (x, y);
}

//////////////////////////////////////////////////////////////////////////

int main()
{
    assert(parse("(1.0, 1.0)") == 1.0 + 1.0i);

    assert(parse("(1.0     )") == 1.0 + 0.0i);

    assert(parse(" 1.0      ") == 1.0 + 0.0i);
}