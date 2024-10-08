#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

#include <gtest/gtest.h>

//  ================================================================================================

namespace parser
{
    struct Huns : boost::spirit::x3::symbols < int >
    {
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

//  ================================================================================================

    struct Tens : boost::spirit::x3::symbols < int >
    {
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
    
//  ================================================================================================

    struct Ones : boost::spirit::x3::symbols < int >
    {
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

//  ================================================================================================

    const boost::spirit::x3::rule < class rule_tag, int > rule;
    
    using boost::spirit::x3::_val;

    const auto set_0 = [](auto && context){ _val(context) = 0; };

    const auto add_M = [](auto && context){ _val(context) += 1'000; };

    const auto add_x = [](auto && context){ _val(context) += boost::spirit::x3::_attr(context); };

    const Huns huns;
    const Tens tens;
    const Ones ones;

    const auto rule_def = 
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

[[nodiscard]] int test(std::string_view data)
{
    int value{};
    
    const auto skip = boost::spirit::x3::ascii::space;

    boost::spirit::x3::phrase_parse(std::cbegin(data), std::cend(data), parser::rule, skip, value);

    return value;
}

//  ================================================================================================

TEST(Parser, Romanus)
{
    ASSERT_EQ(test("MCMLXX"), 1970);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}