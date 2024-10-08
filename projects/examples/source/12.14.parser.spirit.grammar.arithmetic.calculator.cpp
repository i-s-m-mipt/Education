#include <cmath>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

using namespace std::literals;

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <gtest/gtest.h>

//  ================================================================================================

namespace detail
{
    struct Sign;
    struct List;

    struct Operand : boost::spirit::x3::variant 
    < 
        double, boost::spirit::x3::forward_ast < Sign > , 
                boost::spirit::x3::forward_ast < List > 
    >
    {
        using base_type::base_type;
        
        using base_type::operator=;
    };

    struct Sign { char c{}; Operand operand; };
    struct Step { char c{}; Operand operand; };

    struct List { Operand head; std::vector < Step > tail; };
}

//  ================================================================================================

BOOST_FUSION_ADAPT_STRUCT(::detail::Sign, c, operand)

BOOST_FUSION_ADAPT_STRUCT(::detail::Step, c, operand)

BOOST_FUSION_ADAPT_STRUCT(::detail::List, head, tail)

//  ================================================================================================

namespace parser
{
    const boost::spirit::x3::rule < struct rule_1_tag, detail::List    > rule_1;
    const boost::spirit::x3::rule < struct rule_2_tag, detail::List    > rule_2;
    const boost::spirit::x3::rule < struct rule_3_tag, detail::Operand > rule_3;

    const auto rule = rule_1;
    
    const auto rule_1_def = rule_2 >> *
    (        
        (boost::spirit::x3::char_('+') >> rule_2) | 
        (boost::spirit::x3::char_('-') >> rule_2)
    );

    const auto rule_2_def = rule_3 >> *
    (
        (boost::spirit::x3::char_('*') >> rule_3) | 
        (boost::spirit::x3::char_('/') >> rule_3)
    );

    const auto rule_3_def = 
    (
        (boost::spirit::x3::char_('+') >> rule_3) | 
        (boost::spirit::x3::char_('-') >> rule_3) | boost::spirit::x3::double_ | 
        (
            '(' >> rule_1 >> ')'
        )
    );

    BOOST_SPIRIT_DEFINE(rule_1, rule_2, rule_3);
}

//  ================================================================================================

struct Calculator
{
    [[nodiscard]] double operator()(double d) const noexcept 
    { 
        return d; 
    }

    [[nodiscard]] double operator()(const detail::Sign & sign) const
    {
        switch (const auto rhs = boost::apply_visitor(*this, sign.operand); sign.c)
        {
            case '+': return        rhs;
            case '-': return -1.0 * rhs;

            default: throw std::runtime_error("invalid sign");
        }
    }

    [[nodiscard]] double operator()(const detail::Step & step, double lhs) const
    {
        switch (const auto rhs = boost::apply_visitor(*this, step.operand); step.c)
        {
            case '+': return lhs + rhs;
            case '-': return lhs - rhs;
            case '*': return lhs * rhs;
            case '/': return lhs / rhs;

            default: throw std::runtime_error("invalid step");
        }
    }

    [[nodiscard]] double operator()(const detail::List & list) const
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

[[nodiscard]] double test(std::string_view data)
{
    const auto skip = boost::spirit::x3::ascii::space;

    detail::List list;

    boost::spirit::x3::phrase_parse(std::cbegin(data), std::cend(data), parser::rule, skip, list);

    return Calculator()(list);
}

//  ================================================================================================

TEST(Parser, Arithmetic)
{
    ASSERT_DOUBLE_EQ(test("+(1 + -(2 - 3)) * 4 / 5"), 1.6);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}