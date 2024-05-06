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
    namespace detail
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

        } huns; // class Huns : boost::spirit::x3::symbols < int >

//  ================================================================================================

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

        } tens; // class Tens : boost::spirit::x3::symbols < int >

//  ================================================================================================

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

        } ones; // class Ones : boost::spirit::x3::symbols < int >

//  ================================================================================================

        const auto set_0 = [](auto && context){ boost::spirit::x3::_val (context)  = 0;    };
        const auto add_M = [](auto && context){ boost::spirit::x3::_val (context) += 1000; };
        const auto add_x = [](auto && context){ boost::spirit::x3::_val (context) += 
                                                boost::spirit::x3::_attr(context);         };

    } // namespace detail

//  ================================================================================================

    using namespace detail;

    const boost::spirit::x3::rule < class roman_tag, int > roman;

    const auto roman_def = 

        boost::spirit::x3::eps       [set_0] >> (
       *boost::spirit::x3::char_('M')[add_M] >> (-huns[add_x] >> -tens[add_x] >> -ones[add_x]));

    BOOST_SPIRIT_DEFINE(roman);

} // namespace parser

//  ================================================================================================

[[nodiscard]] int test(std::string_view input)
{
    auto begin = std::cbegin(input), end = std::cend(input);

    auto number = 0;

    const auto result = boost::spirit::x3::parse(begin, end, parser::roman, number);

    if (!result || begin != end) 
    {
        throw std::invalid_argument("invalid input: " + std::string(input));
    }

    return number;
}

//  ================================================================================================

TEST(Parser, Romanus)
{
    ASSERT_EQ(test("MCCCLIII"), 1353);
    ASSERT_EQ(test("MCMXVIII"), 1918);
    ASSERT_EQ(test("MCMXCVII"), 1997);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}