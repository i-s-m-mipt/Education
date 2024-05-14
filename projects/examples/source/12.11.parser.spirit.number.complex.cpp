#include <complex>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

#include <gtest/gtest.h>

//  ================================================================================================

[[nodiscard]] std::complex < double > parse_complex(std::string_view input)
{
    auto begin = std::cbegin(input), end = std::cend(input);

    using boost::spirit::x3::double_;

    auto real = 0.0, imag = 0.0;

    const auto f_r = [&real](auto && context){ real =        boost::spirit::x3::_attr(context); };
    const auto f_p = [&imag](auto && context){ imag = +1.0 * boost::spirit::x3::_attr(context); };
    const auto f_n = [&imag](auto && context){ imag = -1.0 * boost::spirit::x3::_attr(context); };

    const auto result = boost::spirit::x3::phrase_parse(begin, end,
    
        (double_[f_r] >> -((('+' >> double_[f_p]) | ('-' >> double_[f_n])) >> 'i')), 
        
            boost::spirit::x3::ascii::space);

    if (!result || begin != end) throw std::runtime_error("invalid input");
            
    return std::complex < double > (real, imag);
}

//  ================================================================================================

TEST(Parser, Complex)
{
    const auto complex_1 = parse_complex("1.0       "sv);
    const auto complex_2 = parse_complex("      1.0i"sv);
    const auto complex_3 = parse_complex("1.0 + 1.0i"sv);
    const auto complex_4 = parse_complex("1.0 - 1.0i"sv);

//  ================================================================================================

    ASSERT_DOUBLE_EQ(complex_1.real(), +1.0); ASSERT_DOUBLE_EQ(complex_1.imag(), +0.0);
    ASSERT_DOUBLE_EQ(complex_2.real(), +0.0); ASSERT_DOUBLE_EQ(complex_2.imag(), +1.0);
    ASSERT_DOUBLE_EQ(complex_3.real(), +1.0); ASSERT_DOUBLE_EQ(complex_3.imag(), -1.0);
    ASSERT_DOUBLE_EQ(complex_4.real(), +1.0); ASSERT_DOUBLE_EQ(complex_4.imag(), -1.0);
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}