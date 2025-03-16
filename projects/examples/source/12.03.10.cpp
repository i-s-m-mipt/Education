#include <cassert>
#include <cmath>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string_view>
#include <vector>

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
public:
    
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

    auto rule_2_def = rule_3 >> *
    (
        boost::spirit::x3::char_('*') >> rule_3 | 

        boost::spirit::x3::char_('/') >> rule_3
    );

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
public:

    auto operator()(double x) const -> double
    { 
        return x;
    }

    auto operator()(const Sign & sign) const -> double
    {
        auto x = boost::apply_visitor(*this, sign.operand);

        switch (sign.operation)
        {
            case '+': { return      x; }

            case '-': { return -1 * x; }

            default: 
            { 
                throw std::runtime_error("invalid operation");
            }
        }
    }

    auto operator()(const Step & step, double x) const -> double
    {
        auto y = boost::apply_visitor(*this, step.operand);

        switch (step.operation)
        {
            case '+': { return x + y; }

            case '-': { return x - y; }

            case '*': { return x * y; }

            case '/': { return x / y; }

            default: 
            {
                throw std::runtime_error("invalid operation");
            }
        }
    }

    auto operator()(const List & list) const -> double
    {
        auto x = boost::apply_visitor(*this, list.head);
        
        for (const auto & step : list.steps)
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

    auto state = boost::spirit::x3::phrase_parse(begin, end, parser::rule_1, space, list);

    if (!state || begin != end)
    {
        throw std::runtime_error("invalid view");
    }

    static Calculator calculator;

    return calculator(list);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(equal(parse("+(1 + -(2 - 3)) * 4 / 5"), 1.6));
}