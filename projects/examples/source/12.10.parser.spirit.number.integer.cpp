#include <cassert>
#include <iterator>
#include <string_view>
#include <tuple>
#include <utility>

using namespace std::literals;

#include <boost/fusion/include/std_tuple.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/spirit/home/x3.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        auto view = "1"sv; auto begin = std::begin(view), end = std::end(view);

        auto rule = boost::spirit::x3::int_;

        auto x = 0;

        boost::spirit::x3::phrase_parse(begin, end, rule, boost::spirit::x3::ascii::space, x);

        assert(x == 1);
    }
    
//  ----------------------------------------------------------------------------------------------

    {
        auto view = "1 1"sv; auto begin = std::begin(view), end = std::end(view);

        auto rule = boost::spirit::x3::int_ >> boost::spirit::x3::int_;

        std::pair < int, int > pair;

        boost::spirit::x3::phrase_parse(begin, end, rule, boost::spirit::x3::ascii::space, pair);

        assert(pair == std::make_pair(1, 1));
    }

//  ----------------------------------------------------------------------------------------------

    {
        auto view = "{ 1 1 }"sv; auto begin = std::begin(view), end = std::end(view);

        auto rule = '{' >> boost::spirit::x3::int_ >> boost::spirit::x3::int_ >> '}';

        std::tuple < int, int > tuple;

        boost::spirit::x3::phrase_parse(begin, end, rule, boost::spirit::x3::ascii::space, tuple);

        assert(tuple == std::make_tuple(1, 1));
    }

//  ----------------------------------------------------------------------------------------------

    {
        auto view = "1"sv; auto begin = std::begin(view), end = std::end(view);

        auto rule = boost::spirit::x3::int_
        [
            (
                [](auto && context)
                { 
                    assert(boost::spirit::x3::_attr(context) == 1); 
                }
            )
        ];

        boost::spirit::x3::phrase_parse(begin, end, rule, boost::spirit::x3::ascii::space);
    }
}