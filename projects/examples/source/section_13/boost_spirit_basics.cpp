#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <utility>

using namespace std::literals;

#include <boost/fusion/include/std_tuple.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/spirit/home/x3.hpp>

int main()
{
    auto value = 0; 
    
    constexpr auto input_1 = "42"sv;

    boost::spirit::x3::parse(std::cbegin(input_1), std::cend(input_1), boost::spirit::x3::int_, value);

    assert(value == 42);

    constexpr auto input_2 = "42 42"sv;

    std::pair < int, int > pair;

    boost::spirit::x3::phrase_parse(std::cbegin(input_2), std::cend(input_2), 
        boost::spirit::x3::int_ >> 
        boost::spirit::x3::int_, 
        boost::spirit::x3::space, pair); // note: skip space characters

    assert(pair.first  == 42);
    assert(pair.second == 42);

    constexpr auto input_3 = "(42, 42)"sv;

    std::tuple < int, int > tuple;

    boost::spirit::x3::phrase_parse(std::cbegin(input_3), std::cend(input_3), '(' >> 
        boost::spirit::x3::int_ >> ',' >> 
        boost::spirit::x3::int_ >> ')', 
        boost::spirit::x3::space, tuple); // note: skip space characters

    assert(std::get < 0 > (tuple) == 42);
    assert(std::get < 1 > (tuple) == 42);

    constexpr auto input_4 = "42"sv;

    const auto f = [](auto & context)
    { 
        std::cout << boost::spirit::x3::_attr(context) << std::endl; 
    };

    boost::spirit::x3::parse(std::cbegin(input_4), std::cend(input_4), boost::spirit::x3::int_[f]);

    return 0;
}