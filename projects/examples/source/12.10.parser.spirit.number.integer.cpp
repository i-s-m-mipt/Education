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

        auto space = boost::spirit::x3::ascii::space;

        auto x = 0;

        assert(boost::spirit::x3::phrase_parse(begin, end, rule, space, x) && begin == end);

        assert(x == 1);
    }
    
//  ----------------------------------------------------------------------------------------------

    {
        auto view = "1 1"sv; auto begin = std::begin(view), end = std::end(view);

        auto rule = boost::spirit::x3::int_ >> boost::spirit::x3::int_;

        auto space = boost::spirit::x3::ascii::space;

        std::pair < int, int > pair;

        assert(boost::spirit::x3::phrase_parse(begin, end, rule, space, pair) && begin == end);       

        assert(pair == std::make_pair(1, 1));
    }

//  ----------------------------------------------------------------------------------------------

    {
        auto view = "{ 1 1 }"sv; auto begin = std::begin(view), end = std::end(view);

        auto rule = '{' >> boost::spirit::x3::int_ >> boost::spirit::x3::int_ >> '}';

        auto space = boost::spirit::x3::ascii::space;

        std::tuple < int, int > tuple;

        assert(boost::spirit::x3::phrase_parse(begin, end, rule, space, tuple) && begin == end);

        assert(tuple == std::make_tuple(1, 1));
    }

//  ----------------------------------------------------------------------------------------------

    {
        auto view = "1"sv; auto begin = std::begin(view), end = std::end(view);

        auto rule = boost::spirit::x3::int_
        [
            ([](auto && context){ assert(boost::spirit::x3::_attr(context) == 1); })
        ];

        auto space = boost::spirit::x3::ascii::space;

        assert(boost::spirit::x3::phrase_parse(begin, end, rule, space) && begin == end);
    }
}