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

    signal_t buffer(size, signal_t::value_type(0));
    
    for (auto i = 0uz; i < size; ++i) 
    {
        for (auto j = 0uz; j < size; ++j) 
        {
            buffer[i] += signal[j] * std::exp(-2.0i * (std::numbers::pi * i * j / size));
        }
    }

    return buffer;
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
    {
        auto x = 1.0 + 1.0i;
        
        auto y = 2.0 + 2.0i;

        assert(equal(std::real(x), 1.000'000));
        assert(equal(std::imag(x), 1.000'000));
        assert(equal(std::abs (x), 1.414'214));
        assert(equal(std::arg (x), 0.785'398));
        assert(equal(std::norm(x), 2.000'000));

        assert(equal(x + y, +3.0 + 3.0i));
        assert(equal(x - y, -1.0 - 1.0i));
        assert(equal(x * y, +0.0 + 4.0i));
        assert(equal(x / y, +0.5 + 0.0i));

        assert(equal(std::conj(x), 1.0 - 1.0i));
        assert(equal(std::proj(x), 1.0 + 1.0i));

        assert(equal(std::polar(std::sqrt(2.0), std::numbers::pi / 4), x));
    }
    
//  --------------------------------------------------------------------------------

    {
        auto signal = transform({ 0.0 + 0.0i, 0.0 + 1.0i, 1.0 + 0.0i, 1.0 + 1.0i });

        assert(equal(signal.at(0), +2.0 + 2.0i));
        assert(equal(signal.at(1), -1.0 + 1.0i));
        assert(equal(signal.at(2), +0.0 - 2.0i));
        assert(equal(signal.at(3), -1.0 - 1.0i));
    }
}