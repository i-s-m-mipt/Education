///////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <complex>
#include <numbers>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////

using signal_t = std::vector < std::complex < double > > ;

///////////////////////////////////////////////////////////////////////////////////////

auto transform(signal_t const & signal)
{
    auto size = std::size(signal);

    signal_t buffer(size, signal_t::value_type(0));
    
    for (auto i = 0uz; i < size; ++i) 
    {
        for (auto j = 0uz; j < size; ++j) 
        {
            buffer[i] += signal[j] * std::exp(-2i * (std::numbers::pi * i * j / size));
        }
    }

    return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////

auto equal(std::complex < double > x, std::complex < double > y, double epsilon = 1e-6)
{
    return 
    (
        std::abs(std::real(x) - std::real(y)) < epsilon &&
        
        std::abs(std::imag(y) - std::imag(y)) < epsilon
    );
}

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto signal = transform({ 0.0 + 0.0i, 0.0 + 1.0i, 1.0 + 0.0i, 1.0 + 1.0i });

//  ----------------------------------------------------------------------------

    assert(equal(signal.at(0), +2.0 + 2.0i));

    assert(equal(signal.at(1), -1.0 + 1.0i));

    assert(equal(signal.at(2), +0.0 - 2.0i));

    assert(equal(signal.at(3), -1.0 - 1.0i));
}

///////////////////////////////////////////////////////////////////////////////////////