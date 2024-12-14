#include <cassert>
#include <complex>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string_view>

#include <boost/spirit/home/x3.hpp>

//  ================================================================================================

auto parse(std::string_view data)
{
    auto begin = std::begin(data), end = std::end(data);

    int value_1, value_2;

    using boost::spirit::x3::_attr;

    auto set_value_1 = [&value_1](auto && context){ value_1 = _attr(context); };
    auto set_value_2 = [&value_2](auto && context){ value_2 = _attr(context); };

    using boost::spirit::x3::double_;

    auto rule = 
    (
        '(' >> double_[set_value_1] >> ',' >> double_[set_value_2] >> ')' |
        '(' >> double_[set_value_1]                                >> ')' |
               double_[set_value_1] >> ',' >> double_[set_value_2]        |
               double_[set_value_1]
    );

    auto skip = boost::spirit::x3::ascii::space;

    auto result = boost::spirit::x3::phrase_parse(begin, end, rule, skip);

    if (!result || begin != end)
    {
        throw std::runtime_error("invalid data");
    }
    
    return std::complex < int > (value_1, value_2);
}

//  ================================================================================================

int main()
{
    assert(parse("(1, 2)") == std::complex < int > (1, 2));
    assert(parse("(1   )") == std::complex < int > (1, 0));
    assert(parse(" 1, 2 ") == std::complex < int > (1, 2));
    assert(parse(" 1    ") == std::complex < int > (1, 0));
}