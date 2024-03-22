#include <cassert>
#include <cmath>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std::literals;

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp> // note: abstract syntax tree

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

BOOST_FUSION_ADAPT_STRUCT(::detail::Sign, c, operand)
BOOST_FUSION_ADAPT_STRUCT(::detail::Step, c, operand)
BOOST_FUSION_ADAPT_STRUCT(::detail::List, head, tail)

class Calculator
{
public:

    [[nodiscard]] double operator()(double n) const noexcept { return n; }

    [[nodiscard]] double operator()(const detail::Sign & sign) const
    {
        switch (auto rhs = boost::apply_visitor(*this, sign.operand); sign.c)
        {
            case '+': return        rhs;
            case '-': return -1.0 * rhs;

            default: throw std::runtime_error("invalid sign: "s + sign.c);
        }
    }

    [[nodiscard]] double operator()(const detail::Step & step, double lhs) const
    {
        switch (auto rhs = boost::apply_visitor(*this, step.operand); step.c)
        {
            case '+': return lhs + rhs;
            case '-': return lhs - rhs;
            case '*': return lhs * rhs;
            case '/': return lhs / rhs;

            default: throw std::runtime_error("invalid step: "s + step.c);
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

namespace grammar
{
    const boost::spirit::x3::rule < class E_tag, detail::List    > expression;
    const boost::spirit::x3::rule < class T_tag, detail::List    > term;
    const boost::spirit::x3::rule < class P_tag, detail::Operand > primary;

    const auto expression_def = term >> *(   
        (boost::spirit::x3::char_('+') >> term) | 
        (boost::spirit::x3::char_('-') >> term));

    const auto term_def = primary >> *(
        (boost::spirit::x3::char_('*') >> primary) | 
        (boost::spirit::x3::char_('/') >> primary));

    const auto primary_def = boost::spirit::x3::double_ | 
            '(' >> expression >> ')' |   
        (boost::spirit::x3::char_('-') >> primary) | 
        (boost::spirit::x3::char_('+') >> primary);

    BOOST_SPIRIT_DEFINE(expression, term, primary);

    auto arithmetic = expression;

} // namespace grammar

[[nodiscard]] double test(std::string_view input)
{
    auto begin = std::begin(input), end = std::end(input);

    detail::List list;

    auto result = boost::spirit::x3::phrase_parse(begin, end, 
        grammar::arithmetic, boost::spirit::x3::ascii::space, list);

    if (!result || begin != end) throw std::runtime_error("invalid input");

    Calculator calculator;

    return calculator(list);
}

int main()
{
    const auto epsilon = 0.000001;

    assert(std::abs(test("+1.0") - +1.0) < epsilon);
    assert(std::abs(test("-1.0") - -1.0) < epsilon);

    assert(std::abs(test("1.0 + 2.0") - +3.0) < epsilon);
    assert(std::abs(test("1.0 - 2.0") - -1.0) < epsilon);
    assert(std::abs(test("1.0 * 2.0") - +2.0) < epsilon);
    assert(std::abs(test("1.0 / 2.0") - +0.5) < epsilon);

    assert(std::abs(test("1.0 + 2.0 + 3.0") - +6.0) < epsilon);
    assert(std::abs(test("1.0 - 2.0 - 3.0") - -4.0) < epsilon);
    assert(std::abs(test("1.0 * 2.0 * 3.0") - +6.0) < epsilon);

    assert(std::abs(test("1.0 / 2.0 / 3.0") - +0.166667) < epsilon);

    assert(std::abs(test("(1.0 + 2.0) * 3.0 - 4.0") - +5.00) < epsilon);
    assert(std::abs(test("1.0 - (2.0 - 3.0) / 4.0") - +1.25) < epsilon);
    assert(std::abs(test("1.0 * 2.0 - (3.0 + 4.0)") - -5.00) < epsilon);

    return 0;
}