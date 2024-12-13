#include <cassert>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

#include <boost/spirit/home/x3.hpp>

//  ================================================================================================

namespace parser
{
    class Huns : public boost::spirit::x3::symbols < int >
    {
    public:

        Huns()
        {
            add("C"   , 100);
            add("CC"  , 200);
            add("CCC" , 300);
            add("CD"  , 400);
            add("D"   , 500);
            add("DC"  , 600);
            add("DCC" , 700);
            add("DCCC", 800);
            add("CM"  , 900);
        }
    };

//  ------------------------------------------------------

    class Tens : public boost::spirit::x3::symbols < int >
    {
    public:

        Tens()
        {
            add("X"   , 10);
            add("XX"  , 20);
            add("XXX" , 30);
            add("XL"  , 40);
            add("L"   , 50);
            add("LX"  , 60);
            add("LXX" , 70);
            add("LXXX", 80);
            add("XC"  , 90);
        }
    };
    
//  ------------------------------------------------------

    class Ones : public boost::spirit::x3::symbols < int >
    {
    public:

        Ones()
        {
            add("I"   , 1);
            add("II"  , 2);
            add("III" , 3);
            add("IV"  , 4);
            add("V"   , 5);
            add("VI"  , 6);
            add("VII" , 7);
            add("VIII", 8);
            add("IX"  , 9);
        }
    };

//  ------------------------------------------------------

    boost::spirit::x3::rule < struct rule_tag, int > rule;

    using boost::spirit::x3::_val;

    auto set_0 = [](auto && context){ _val(context) = 0; };

    auto add_M = [](auto && context){ _val(context) += 1'000; };

    auto add_x = [](auto && context){ _val(context) += boost::spirit::x3::_attr(context); };

    Huns huns;
    Tens tens;
    Ones ones;

    auto rule_def = 
    (
        boost::spirit::x3::eps       [set_0] >>
       *boost::spirit::x3::char_('M')[add_M] >> 
        (
            -huns[add_x] >> 
            -tens[add_x] >> 
            -ones[add_x]
        )
    );

    BOOST_SPIRIT_DEFINE(rule);
}

//  ================================================================================================

auto parse(std::string_view data)
{
    auto begin = std::cbegin(data), end = std::cend(data);

    auto skip = boost::spirit::x3::ascii::space;

    int value;

    auto result = boost::spirit::x3::phrase_parse(begin, end, parser::rule, skip, value);

    if (!result || begin != end)
    {
        throw std::runtime_error("invalid data");
    }
    
    return value;
}

//  ================================================================================================

int main()
{
    assert(parse("MCMLXX") == 1970);
}