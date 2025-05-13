///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <istream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

class Operand : public boost::spirit::x3::variant 
< 
    double, boost::spirit::x3::forward_ast < struct Sign > ,

            boost::spirit::x3::forward_ast < struct List > 
>
{
public :
    
    using base_type::base_type, base_type::operator=;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

struct Sign { char operation = '\0'; Operand operand; };
    
struct Step { char operation = '\0'; Operand operand; };

///////////////////////////////////////////////////////////////////////////////////////////////////

struct List 
{ 
    Operand head;
        
    std::vector < Step > steps;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_FUSION_ADAPT_STRUCT(Sign, operation, operand)

BOOST_FUSION_ADAPT_STRUCT(Step, operation, operand)

///////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_FUSION_ADAPT_STRUCT(List, head, steps)

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace parser
{
    boost::spirit::x3::rule < struct rule_1_tag, List    > rule_1;

    boost::spirit::x3::rule < struct rule_2_tag, List    > rule_2;

    boost::spirit::x3::rule < struct rule_3_tag, Operand > rule_3;

//  -----------------------------------------------------------------------------------------------

    auto rule_1_def = rule_2 >> *
    (        
        boost::spirit::x3::char_('+') >> rule_2 | 

        boost::spirit::x3::char_('-') >> rule_2
    );

//  -----------------------------------------------------------------------------------------------

    auto rule_2_def = rule_3 >> *
    (
        boost::spirit::x3::char_('*') >> rule_3 | 

        boost::spirit::x3::char_('/') >> rule_3
    );

//  -----------------------------------------------------------------------------------------------

    auto rule_3_def = 
    (
        boost::spirit::x3::char_('+') >> rule_3 | 

        boost::spirit::x3::char_('-') >> rule_3 | boost::spirit::x3::double_ | '(' >> rule_1 >> ')'
    );

//  -----------------------------------------------------------------------------------------------

    BOOST_SPIRIT_DEFINE(rule_1, rule_2, rule_3);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

class Calculator
{
public :

    auto operator()(double x) const -> double
    { 
        return x;
    }

//  ------------------------------------------------------------

    auto operator()(Sign const & sign) const -> double
    {
        auto x = boost::apply_visitor(*this, sign.operand);

        switch (sign.operation)
        {
            case '+' : { return      x; }

            case '-' : { return -1 * x; }
        }

        return x;
    }

//  ------------------------------------------------------------

    auto operator()(Step const & step, double x) const -> double
    {
        auto y = boost::apply_visitor(*this, step.operand);

        switch (step.operation)
        {
            case '+' : { return x + y; }

            case '-' : { return x - y; }

            case '*' : { return x * y; }

            case '/' : { return x / y; }
        }

        return x;
    }

//  ------------------------------------------------------------

    auto operator()(List const & list) const -> double
    {
        auto x = boost::apply_visitor(*this, list.head);
        
        for (auto const & step : list.steps)
        {
            x = (*this)(step, x);
        }

        return x;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////

auto parse(std::string_view view)
{
    auto begin = std::begin(view), end = std::end(view);

    auto space = boost::spirit::x3::ascii::space;

    List list;

    boost::spirit::x3::phrase_parse(begin, end, parser::rule_1, space, list);

    static Calculator calculator;

    return calculator(list);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::string string;

//  ---------------------------------------------------------------------------

    std::cout << "main : enter std::string string(s) : \n";

//  ---------------------------------------------------------------------------
		
	while (std::getline(std::cin >> std::ws, string))
	{
        if (string.front() != ';')
        {
            std::cout << "main : " << string << " = " << parse(string) << '\n';
        }
		else
        {
            break;
        }
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////