//////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iterator>
#include <string_view>

//////////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

//////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/spirit/home/x3.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto view = "1"sv;

//  ------------------------------------------------------------------------------------------
        
    auto begin = std::begin(view), end = std::end(view);

//  ------------------------------------------------------------------------------------------

    auto lambda = [](auto const & context){ assert(boost::spirit::x3::_attr(context) == 1); };

//  ------------------------------------------------------------------------------------------

    auto rule = boost::spirit::x3::int_[lambda];

//  ------------------------------------------------------------------------------------------

    auto space = boost::spirit::x3::ascii::space;

//  ------------------------------------------------------------------------------------------

    boost::spirit::x3::phrase_parse(begin, end, rule, space);
}

//////////////////////////////////////////////////////////////////////////////////////////////