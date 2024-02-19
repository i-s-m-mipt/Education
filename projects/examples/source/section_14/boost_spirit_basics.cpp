#include <cassert>
#include <iterator>
#include <string>
#include <tuple>
#include <utility>

#include <boost/fusion/include/std_tuple.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/spirit/home/x3.hpp>

int main()
{
    auto value = 0; 
    
    std::string input_1("42");

    auto begin_1 = std::begin(input_1);
    auto   end_1 = std::  end(input_1);

    boost::spirit::x3::parse(begin_1, end_1, 
        boost::spirit::x3::int_, value);

    assert(value == 42);

    std::string input_2("42 42");

    auto begin_2 = std::begin(input_2);
    auto   end_2 = std::  end(input_2);

    std::pair < int, int > pair;

    boost::spirit::x3::phrase_parse(begin_2, end_2,
        boost::spirit::x3::int_ >> 
        boost::spirit::x3::int_, 
        boost::spirit::x3::space, pair);

    assert(pair.first  == 42);
    assert(pair.second == 42);

    std::string input_3("(42, 42)");

    auto begin_3 = std::begin(input_3);
    auto   end_3 = std::  end(input_3);

    std::tuple < int, int > tuple;

    boost::spirit::x3::parse(begin_3, end_3, '(' >> 
        boost::spirit::x3::int_ >> ", " >> 
        boost::spirit::x3::int_ >> ')', tuple);

    assert(std::get < 0 > (tuple) == 42);
    assert(std::get < 1 > (tuple) == 42);

    return 0;
}