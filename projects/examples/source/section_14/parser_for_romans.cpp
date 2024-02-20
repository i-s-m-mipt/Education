#include <iostream>
#include <string>

#include <boost/spirit/home/x3.hpp>

    namespace x3 = boost::spirit::x3;
    namespace ascii = boost::spirit::x3::ascii;

struct Hundreds : boost::spirit::x3::symbols < unsigned int >
{
    Hundreds()
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

}; // struct Hundreds : boost::spirit::x3::symbols < unsigned int >

struct Tens : boost::spirit::x3::symbols < unsigned int >
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

}; // struct Tens : boost::spirit::x3::symbols < unsigned int >

struct Ones : boost::spirit::x3::symbols < unsigned int >
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

}; // struct Ones : boost::spirit::x3::symbols < unsigned int >


    namespace parser
    {
        using x3::eps;
        using x3::lit;
        using x3::_val;
        using x3::_attr;
        using ascii::char_;

        auto set_zero = [](auto& ctx){ _val(ctx) = 0; };
        auto add1000 = [](auto& ctx){ _val(ctx) += 1000; };
        auto add = [](auto& ctx){ _val(ctx) += _attr(ctx); };

        x3::rule<class roman, unsigned> const roman = "roman";

        auto const roman_def =
            eps                 [set_zero]
            >>
            (
                -(+lit('M')     [add1000])
                >>  -hundreds   [add]
                >>  -tens       [add]
                >>  -ones       [add]
            )
        ;

        BOOST_SPIRIT_DEFINE(roman);
    }
}

int main()
{
    typedef std::string::const_iterator iterator_type;
    using client::parser::roman; // Our parser

    std::string str;
    unsigned result;
    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        iterator_type iter = str.begin();
        iterator_type const end = str.end();
        bool r = parse(iter, end, roman, result);

        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "result = " << result << std::endl;
            std::cout << "-------------------------\n";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: \": " << rest << "\"\n";
            std::cout << "-------------------------\n";
        }
    }

    return 0;
}