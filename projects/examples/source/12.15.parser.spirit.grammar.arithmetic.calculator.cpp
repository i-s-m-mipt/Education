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
#include <boost/spirit/home/x3/support/ast/variant.hpp> // note: abstract syntax tree

#include <gtest/gtest.h>

// =================================================================================================

namespace detail
{
    struct Sign;
    struct List;

    class Operand : public boost::spirit::x3::variant < double, 
    
        boost::spirit::x3::forward_ast < Sign > , 
        boost::spirit::x3::forward_ast < List > > // note: pattern visitor
    {
    public:

        using base_type::base_type;
        using base_type::operator=;

    }; // class Operand : boost::spirit::x3::variant < ... >

    struct Sign { char c{}; Operand operand; };
    struct Step { char c{}; Operand operand; };

    struct List { Operand head; std::vector < Step > tail; };

} // namespace detail

// =================================================================================================

BOOST_FUSION_ADAPT_STRUCT(::detail::Sign, c, operand)
BOOST_FUSION_ADAPT_STRUCT(::detail::Step, c, operand)
BOOST_FUSION_ADAPT_STRUCT(::detail::List, head, tail)

// =================================================================================================

namespace parser
{
    const boost::spirit::x3::rule < class E_tag, detail::List    > expression;
    const boost::spirit::x3::rule < class T_tag, detail::List    > term;
    const boost::spirit::x3::rule < class P_tag, detail::Operand > primary;

    const auto expression_def = term >> *(
        
        (boost::spirit::x3::char_('+') >> term) | 
        (boost::spirit::x3::char_('-') >> term));

    const auto term_def =  primary >> *(
        
        (boost::spirit::x3::char_('*') >> primary) | 
        (boost::spirit::x3::char_('/') >> primary));

    const auto primary_def = (boost::spirit::x3::double_) | ('(' >> expression >> ')') |  

        (boost::spirit::x3::char_('-') >> primary) | 
        (boost::spirit::x3::char_('+') >> primary);

    BOOST_SPIRIT_DEFINE(expression, term, primary);

    auto arithmetic = expression;

} // namespace parser

// =================================================================================================

class Calculator
{
public:

    [[nodiscard]] double operator()(double d) const noexcept { return d; }

    [[nodiscard]] double operator()(const detail::Sign & sign) const
    {
        switch (const auto rhs = boost::apply_visitor(*this, sign.operand); sign.c)
        {
            case '+': return        rhs;
            case '-': return -1.0 * rhs;

            default: throw std::invalid_argument("invalid sign: "s + sign.c);
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

            default: throw std::invalid_argument("invalid step: "s + step.c);
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

}; // class Calculator

// =================================================================================================

[[nodiscard]] double test(std::string_view input)
{
    auto begin = std::cbegin(input), end = std::cend(input);

    detail::List list;

    auto result = boost::spirit::x3::phrase_parse(begin, end, 
        parser::arithmetic, boost::spirit::x3::ascii::space, list);

    if (!result || begin != end) 
    {
        throw std::invalid_argument("invalid input: " + std::string(input));
    }

    return Calculator()(list);
}

// =================================================================================================

TEST(Parser, Arithmetic)
{
    ASSERT_DOUBLE_EQ(test("+1.0"), +1.0);
    ASSERT_DOUBLE_EQ(test("-1.0"), -1.0);

    ASSERT_DOUBLE_EQ(test("1.0 + 2.0"), +3.0);
    ASSERT_DOUBLE_EQ(test("1.0 - 2.0"), -1.0);
    ASSERT_DOUBLE_EQ(test("1.0 * 2.0"), +2.0);
    ASSERT_DOUBLE_EQ(test("1.0 / 2.0"), +0.5);

    ASSERT_DOUBLE_EQ(test("1.0 + 2.0 + 3.0"), +6.0);
    ASSERT_DOUBLE_EQ(test("1.0 - 2.0 - 3.0"), -4.0);
    ASSERT_DOUBLE_EQ(test("1.0 * 2.0 * 3.0"), +6.0);

    ASSERT_DOUBLE_EQ(test("1.0 / 2.0 / 3.0"), +1.0 / 6.0);

    ASSERT_DOUBLE_EQ(test("(1.0 + 2.0) * 3.0 - 4.0"), +5.00);
    ASSERT_DOUBLE_EQ(test("1.0 - (2.0 - 3.0) / 4.0"), +1.25);
    ASSERT_DOUBLE_EQ(test("1.0 * 2.0 - (3.0 + 4.0)"), -5.00);
}

// =================================================================================================

int main(int argc, char ** argv) // note: arguments for testing
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}