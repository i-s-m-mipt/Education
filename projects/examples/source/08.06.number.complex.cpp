#include <cassert>
#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numbers>
#include <vector>

using namespace std::literals;

//  ================================================================================================

using signal_t = std::vector < std::complex < double > > ;

//  ================================================================================================

auto generate(std::size_t size)
{
    signal_t signal(size, signal_t::value_type(0));

    for (auto i = 0uz; i < size; ++i)
    {
        signal[i] = std::sin(2.0 * i * std::numbers::pi / size);
    }

    return signal;
}

//  ================================================================================================

auto transform(const signal_t & signal)
{
    auto size = std::size(signal);

    signal_t result(size, signal_t::value_type(0));
    
    for (auto i = 0uz; i < size; ++i) 
    {
        for (auto j = 0uz; j < size; ++j) 
        {
            result[i] += signal[j] * std::exp(-2.0i * (std::numbers::pi * i * j / size));
        }
    }

    return result;
}

//  ================================================================================================

auto & operator<<(std::ostream & stream, const signal_t & signal)
{
    stream << "{ ";

    for (auto element : signal) 
    {
        std::cout << std::showpos << std::setprecision(3) << std::fixed << element.real() << ' ';
    }

    return stream << '}';
}

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

auto equal(std::complex < double > x, std::complex < double > y, double epsilon = 1e-6)
{
    return 
    (
        std::abs(x.real() - y.real()) < epsilon &&
        std::abs(x.imag() - y.imag()) < epsilon
    );
}

//  ================================================================================================

int main()
{
    std::complex < double > complex(1.0, 1.0);
    
//  ------------------------------------------

    assert(equal(complex.real(), 1.0));
    assert(equal(complex.imag(), 1.0));

//  ---------------------------------------------

    assert(equal(std::abs (complex), 1.414'214));
    assert(equal(std::norm(complex), 2.000'000));

//  ------------------------------------------------------------------------------------

    assert(equal(std::conj(complex), std::complex < double > (+1.000'000, -1.000'000)));
    assert(equal(std::proj(complex), std::complex < double > (+1.000'000, +1.000'000)));
    assert(equal(std::exp (complex), std::complex < double > (+1.468'694, +2.287'355)));
    assert(equal(std::log (complex), std::complex < double > (+0.346'574, +0.785'398)));
    assert(equal(std::sqrt(complex), std::complex < double > (+1.098'684, +0.455'090)));

//  ------------------------------------------------------------------------------------

    assert(equal(complex + complex , std::complex < double > (+2.000'000, +2.000'000)));
    assert(equal(complex - complex , std::complex < double > (+0.000'000, +0.000'000)));
    assert(equal(complex * complex , std::complex < double > (+0.000'000, +2.000'000)));
    assert(equal(complex / complex , std::complex < double > (+1.000'000, +0.000'000)));

//  ------------------------------------------------------------------------------------

    decltype(complex)::value_type p1 = 1.0, p2 = 1.0;

    assert(equal(std::polar(p1, p2), std::complex < double > (+0.540'302, +0.841'471)));

//  ------------------------------------------------------------------------------------------------

    auto signal = generate(8);

    std::cout << "signal = " << signal << '\n';

    auto result = transform(signal);

    std::cout << "result = " << result << '\n';
}