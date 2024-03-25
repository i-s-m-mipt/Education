#include <cassert>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std::literals;

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>

struct Data { char c{}; int i{}; double d{}; }; 

BOOST_FUSION_ADAPT_STRUCT(Data, c, i, d) // note: global scope

namespace parser
{
    const boost::spirit::x3::rule < class data_tag, Data > data;

    const auto quote = '\'', separator = ',';

    auto const data_def = '{' >> 
        boost::spirit::x3::lexeme[ quote  >> 
       (boost::spirit::x3::char_ - quote) >> quote ] >> separator >> 
        boost::spirit::x3::int_                      >> separator >> 
        boost::spirit::x3::double_ >> '}';

    BOOST_SPIRIT_DEFINE(data);

} // namespace parser

int main()
{
    auto input = R"({'a',100,1.0})"sv;

    auto begin = std::begin(input), end = std::end(input);

    Data data;

    auto result = boost::spirit::x3::parse(begin, end, parser::data, data);

    if (!result || begin != end) 
    {
        throw std::invalid_argument("invalid input: " + std::string(input));
    }

    assert(data.c == 'a');
    assert(data.i == 100);
    assert(data.d == 1.0);

    return 0;
}