/////////////////////////////////////////////////////////////////////////////////////////

// chapter : Characters

/////////////////////////////////////////////////////////////////////////////////////////

// content : Complex Number Parser

/////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <complex>
#include <iterator>
#include <string_view>

/////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////////////////////

#include <boost/spirit/home/x3.hpp>

/////////////////////////////////////////////////////////////////////////////////////////

auto parse(std::string_view view)
{
    auto x = 0.0, y = 0.0;

    auto lambda_1 = [&x](auto const & context){ x = boost::spirit::x3::_attr(context); };

    auto lambda_2 = [&y](auto const & context){ y = boost::spirit::x3::_attr(context); };

    using boost::spirit::x3::double_;

    auto rule =
    (
        '(' >> double_[lambda_1] >> ',' >> double_[lambda_2] >> ')' |

        '(' >> double_[lambda_1]                             >> ')' |

               double_[lambda_1]
    );

    boost::spirit::x3::phrase_parse
    (
        std::begin(view), std::end(view), rule, boost::spirit::x3::ascii::space
    );

    return std::complex < double > (x, y);
}

/////////////////////////////////////////////////////////////////////////////////////////

auto equal(std::complex < double > x, std::complex < double > y, double epsilon = 1e-6)
{
    return
    (
        std::abs(std::real(x) - std::real(y)) < epsilon &&

        std::abs(std::imag(y) - std::imag(y)) < epsilon
    );
}

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(equal(parse("(1.0, 1.0)"), 1.0 + 1.0i));

    assert(equal(parse("(1.0)     "), 1.0 + 0.0i));

    assert(equal(parse(" 1.0      "), 1.0 + 0.0i));
}

/////////////////////////////////////////////////////////////////////////////////////////