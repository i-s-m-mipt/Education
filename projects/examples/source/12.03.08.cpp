#include <cassert>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string_view>

#include <boost/spirit/home/x3.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////

namespace parser
{
    class Handler_v1 : public boost::spirit::x3::symbols < int >
    {
    public:

        Handler_v1()
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

//  -------------------------------------------------------------------------------------------

    class Handler_v2 : public boost::spirit::x3::symbols < int >
    {
    public:

        Handler_v2()
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
    
//  -------------------------------------------------------------------------------------------

    class Handler_v3 : public boost::spirit::x3::symbols < int >
    {
    public:

        Handler_v3()
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

//  -------------------------------------------------------------------------------------------

    boost::spirit::x3::rule < struct rule_tag, int > rule;

//  -------------------------------------------------------------------------------------------

    using boost::spirit::x3::_val;

//  -------------------------------------------------------------------------------------------

    auto lambda_1 = [](auto && context){ _val(context) = 0; };

    auto lambda_2 = [](auto && context){ _val(context) += 1'000; };

    auto lambda_3 = [](auto && context){ _val(context) += boost::spirit::x3::_attr(context); };

//  -------------------------------------------------------------------------------------------

    Handler_v1 handler_v1;
    
    Handler_v2 handler_v2;
    
    Handler_v3 handler_v3;

//  -------------------------------------------------------------------------------------------

    auto rule_def = 
    (
        boost::spirit::x3::eps[lambda_1] >> *boost::spirit::x3::char_('M')[lambda_2] >> 
        (
            -handler_v1[lambda_3] >> 
            
            -handler_v2[lambda_3] >> 
            
            -handler_v3[lambda_3]
        )
    );

//  -------------------------------------------------------------------------------------------

    BOOST_SPIRIT_DEFINE(rule);
}

///////////////////////////////////////////////////////////////////////////////////////////////

auto parse(std::string_view view)
{
    auto begin = std::begin(view), end = std::end(view);

    auto space = boost::spirit::x3::ascii::space;

    auto x = 0;

    auto state = boost::spirit::x3::phrase_parse(begin, end, parser::rule, space, x);

    if (!state || begin != end)
    {
        throw std::runtime_error("invalid view");
    }
    
    return x;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(parse("MCMLXX") == 1'970);
}