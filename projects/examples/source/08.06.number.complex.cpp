#include <cassert>
#include <cmath>
#include <complex>
#include <numbers>
#include <vector>

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////////////////////

using signal_t = std::vector < std::complex < double > > ;

/////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
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
    auto complex = 1.0 + 1.0i;

    assert(equal(std::real(complex), 1.000'000));
    assert(equal(std::imag(complex), 1.000'000));

    assert(equal(complex + complex , 2.000'000 + 2.000'000i));
    assert(equal(complex - complex , 0.000'000 + 0.000'000i));
    assert(equal(complex * complex , 0.000'000 + 2.000'000i));
    assert(equal(complex / complex , 1.000'000 + 0.000'000i));

    assert(equal(std::abs (complex), 1.414'214));
    assert(equal(std::arg (complex), 0.785'398));
    assert(equal(std::norm(complex), 2.000'000));

    assert(equal(std::conj(complex), 1.000'000 - 1.000'000i));
    assert(equal(std::proj(complex), 1.000'000 + 1.000'000i));

    assert(equal(std::polar(std::sqrt(2.0), std::numbers::pi / 4), complex));

//  -------------------------------------------------------------------------

    auto result = transform({ 0.0 + 0.0i, 0.0 + 1.0i, 1.0 + 0.0i, 1.0 + 1.0i });

    assert(equal(result.at(0), +2.0 + 2.0i));
    assert(equal(result.at(1), -1.0 + 1.0i));
    assert(equal(result.at(2), +0.0 - 2.0i));
    assert(equal(result.at(3), -1.0 - 1.0i));
}