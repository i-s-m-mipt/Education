#include <cassert>
#include <complex>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>

using namespace std::literals;

#include <boost/spirit/home/x3.hpp>

template < typename Iterator > std::complex < double > parse_complex(Iterator first, Iterator last)
{
    using boost::spirit::x3::double_;

    auto real = 0.0, imag = 0.0;

    auto f_real   = [&real](auto & context){ real =        boost::spirit::x3::_attr(context); };
    auto f_imag_p = [&imag](auto & context){ imag = +1.0 * boost::spirit::x3::_attr(context); };
    auto f_imag_n = [&imag](auto & context){ imag = -1.0 * boost::spirit::x3::_attr(context); };

    auto result = boost::spirit::x3::phrase_parse(first, last,
        (double_[f_real] >> -((
            ('+' >> double_[f_imag_p]) | 
            ('-' >> double_[f_imag_n])) >> 'i') | double_[f_real]), boost::spirit::x3::ascii::space);

    if (!result || first != last) throw std::runtime_error("invalid input");
            
    return std::complex < double > (real, imag);
}

int main()
{
    auto input_1 = "1.0"s; 
    auto input_2 = "1.0+1.0i"s;
    auto input_3 = "1.0-1.0i"s;
    auto input_4 = " 1.0 + 1.0 i "s;
    
    auto complex_1 = parse_complex(std::begin(input_1), std::end(input_1));
    auto complex_2 = parse_complex(std::begin(input_2), std::end(input_2));
    auto complex_3 = parse_complex(std::begin(input_3), std::end(input_3));
    auto complex_4 = parse_complex(std::begin(input_4), std::end(input_4));

    assert(complex_1.real() == 1.0 && complex_1.imag() == +0.0);
    assert(complex_2.real() == 1.0 && complex_2.imag() == +1.0);
    assert(complex_3.real() == 1.0 && complex_3.imag() == -1.0);
    assert(complex_4.real() == 1.0 && complex_4.imag() == +1.0);

    return 0;
}