#include <cassert>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

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

        auto set_0    = [](auto & context){ boost::spirit::x3::_val (context)  = 0;    };
        auto add_1000 = [](auto & context){ boost::spirit::x3::_val (context) += 1000; };
        auto add_x    = [](auto & context){ boost::spirit::x3::_val (context) += 
                                            boost::spirit::x3::_attr(context); };

    } // namespace detail

    using namespace detail; // note: namespaces used in documentation, consider classes

    const boost::spirit::x3::rule < class roman_tag, int > roman; // note: tag, attribute

    const auto roman_def = 
        boost::spirit::x3::eps       [set_0   ] >> ( // note: dummy element, always works
       *boost::spirit::x3::char_('M')[add_1000] >> 
            -huns[add_x] >> 
            -tens[add_x] >> 
            -ones[add_x]);

    BOOST_SPIRIT_DEFINE(roman); // note: generates parse_rule function for roman parser

} // namespace parser

[[nodiscard]] int test(const std::string & input)
{
    auto begin = std::begin(input), end = std::end(input);

    auto number = 0;

    auto result = boost::spirit::x3::parse(begin, end, parser::roman, number);

    if (!result || begin != end) throw std::runtime_error("invalid input");

    return number;
}

int main()
{
    assert(test("MCCCLIII") == 1353);
    assert(test("MCMXVIII") == 1918);
    assert(test("MCMXCVII") == 1997);

    return 0;
}