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

//  ================================================================================================

namespace detail
{
    class Operand : public boost::spirit::x3::variant 
    < 
        double, boost::spirit::x3::forward_ast < struct Sign > , 
                boost::spirit::x3::forward_ast < struct List > 
    >
    {
    public:
    
        using base_type::base_type, base_type::operator=;
    };

    struct Sign { char operation = '\0'; Operand operand; };
    
    struct Step { char operation = '\0'; Operand operand; };

    struct List 
    { 
        Operand head; std::vector < Step > tail; 
    };
}

//  ================================================================================================

BOOST_FUSION_ADAPT_STRUCT(::detail::Sign, operation, operand)

BOOST_FUSION_ADAPT_STRUCT(::detail::Step, operation, operand)

BOOST_FUSION_ADAPT_STRUCT(::detail::List, head, tail)

//  ================================================================================================

namespace parser
{
    boost::spirit::x3::rule < struct rule_1_tag, detail::List    > rule_1;
    boost::spirit::x3::rule < struct rule_2_tag, detail::List    > rule_2;
    boost::spirit::x3::rule < struct rule_3_tag, detail::Operand > rule_3;

    auto rule_1_def = rule_2 >> *
    (        
        (boost::spirit::x3::char_('+') >> rule_2) | 
        (boost::spirit::x3::char_('-') >> rule_2)
    );

    auto rule_2_def = rule_3 >> *
    (
        (boost::spirit::x3::char_('*') >> rule_3) | 
        (boost::spirit::x3::char_('/') >> rule_3)
    );

    auto rule_3_def = 
    (
        (boost::spirit::x3::char_('+') >> rule_3) | 
        (boost::spirit::x3::char_('-') >> rule_3) | boost::spirit::x3::double_ | 
        (
            '(' >> rule_1 >> ')'
        )
    );

    BOOST_SPIRIT_DEFINE(rule_1, rule_2, rule_3);

    auto rule = rule_1;
}

//  ================================================================================================

class Calculator
{
public:

    auto operator()(double d) const -> double
    { 
        return d; 
    }

    auto operator()(const detail::Sign & sign) const -> double
    {
        switch (auto rhs = boost::apply_visitor(*this, sign.operand); sign.operation)
        {
            case '+': { return        rhs; }
            case '-': { return -1.0 * rhs; }

            default: 
            { 
                throw std::runtime_error("invalid data"); 
            }
        }
    }

    auto operator()(const detail::Step & step, double lhs) const -> double
    {
        switch (auto rhs = boost::apply_visitor(*this, step.operand); step.operation)
        {
            case '+': { return lhs + rhs; }
            case '-': { return lhs - rhs; }
            case '*': { return lhs * rhs; }
            case '/': { return lhs / rhs; }

            default: 
            {
                throw std::runtime_error("invalid data");
            }
        }
    }

    auto operator()(const detail::List & list) const -> double
    {
        auto state = boost::apply_visitor(*this, list.head);
        
        for (const auto & step : list.tail)
        {
            state = (*this)(step, state);
        }

        return state;
    }
};

//  ================================================================================================

auto parse(std::string_view data)
{
    auto begin = std::begin(data), end = std::end(data);

    auto skip = boost::spirit::x3::ascii::space;

    detail::List list;

    auto result = boost::spirit::x3::phrase_parse(begin, end, parser::rule, skip, list);

    if (!result || begin != end)
    {
        throw std::runtime_error("invalid data");
    }

    return Calculator()(list);
}

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main()
{
    assert(equal(parse("+(1 + -(2 - 3)) * 4 / 5"), 1.6));
}