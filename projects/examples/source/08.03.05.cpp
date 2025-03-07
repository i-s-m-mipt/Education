#include <cassert>
#include <cmath>
#include <complex>

using namespace std::literals;

/////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////

int main()
{
    auto x = 1.0 + 1.0i;

//  ---------------------------------------

    assert(equal(std::real(x), 1.000'000));

    assert(equal(std::imag(x), 1.000'000));

    assert(equal(std::norm(x), 2.000'000));

    assert(equal(std::abs (x), 1.414'214));

    assert(equal(std::arg (x), 0.785'398));
}