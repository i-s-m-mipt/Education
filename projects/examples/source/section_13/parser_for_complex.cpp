#include <cassert>
#include <complex>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

[[nodiscard]] std::complex < double > parse_complex(std::string_view input)
{
    auto begin = std::cbegin(input), end = std::cend(input);

    using boost::spirit::x3::double_;

    auto real = 0.0, imag = 0.0;

    const auto f_real   = [&real](auto & context){ real =        boost::spirit::x3::_attr(context); };
    const auto f_imag_p = [&imag](auto & context){ imag = +1.0 * boost::spirit::x3::_attr(context); };
    const auto f_imag_n = [&imag](auto & context){ imag = -1.0 * boost::spirit::x3::_attr(context); };

    const auto result = boost::spirit::x3::phrase_parse(begin, end,
        (double_[f_real] >> -((
            ('+' >> double_[f_imag_p]) | 
            ('-' >> double_[f_imag_n])) >> 'i')), boost::spirit::x3::ascii::space);

    if (!result || begin != end) 
    {
        throw std::invalid_argument("invalid input: " + std::string(input));
    }
            
    return std::complex < double > (real, imag);
}

int main()
{
    const auto complex_1 = parse_complex("1.0"sv          );
    const auto complex_2 = parse_complex("1.0+1.0i"sv     );
    const auto complex_3 = parse_complex("1.0-1.0i"sv     );
    const auto complex_4 = parse_complex(" 1.0 + 1.0 i "sv);

    assert(complex_1.real() == 1.0 && complex_1.imag() == +0.0);
    assert(complex_2.real() == 1.0 && complex_2.imag() == +1.0);
    assert(complex_3.real() == 1.0 && complex_3.imag() == -1.0);
    assert(complex_4.real() == 1.0 && complex_4.imag() == +1.0);

    return 0;
}