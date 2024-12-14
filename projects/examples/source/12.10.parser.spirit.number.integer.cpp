#include <cassert>
#include <iterator>
#include <string_view>
#include <tuple>
#include <utility>

using namespace std::literals;

#include <boost/fusion/include/std_tuple.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/spirit/home/x3.hpp>

int main()
{
    auto skip = boost::spirit::x3::ascii::space;

    auto data_1 = "1"sv; auto begin_1 = std::cbegin(data_1), end_1 = std::cend(data_1);

    auto rule_1 = boost::spirit::x3::int_;

    auto value = 0;

    boost::spirit::x3::phrase_parse(begin_1, end_1, rule_1, skip, value);

    assert(value == 1);
    
//  -------------------------------------------------------------------------------------

    auto data_2 = "1 2"sv; auto begin_2 = std::cbegin(data_2), end_2 = std::cend(data_2);

    auto rule_2 = boost::spirit::x3::int_ >> boost::spirit::x3::int_;

    std::pair < int, int > pair;

    boost::spirit::x3::phrase_parse(begin_2, end_2, rule_2, skip, pair);

    assert(pair == std::make_pair(1, 2));

//  ----------------------------------------------------------------------------------------

    auto data_3 = "(1, 2)"sv; auto begin_3 = std::cbegin(data_3), end_3 = std::cend(data_3);

    auto rule_3 = '(' >> boost::spirit::x3::int_ >> ',' >> boost::spirit::x3::int_ >> ')';

    std::tuple < int, int > tuple;

    boost::spirit::x3::phrase_parse(begin_3, end_3, rule_3, skip, tuple);

    assert(tuple == std::make_tuple(1, 2));

//  -----------------------------------------------------------------------------------

    auto data_4 = "1"sv; auto begin_4 = std::cbegin(data_4), end_4 = std::cend(data_4);

    auto rule_4 = boost::spirit::x3::int_
    [
        (
            [](auto && context)
            { 
                assert(boost::spirit::x3::_attr(context) == 1); 
            }
        )
    ];

    boost::spirit::x3::phrase_parse(begin_4, end_4, rule_4, skip);
}