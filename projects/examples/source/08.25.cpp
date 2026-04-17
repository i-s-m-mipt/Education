///////////////////////////////////////////////////////////////////////////////////////

// chapter : Arithmetic

///////////////////////////////////////////////////////////////////////////////////////

// section : Floating-Point Numbers

///////////////////////////////////////////////////////////////////////////////////////

// content : Direct Fourier Transform Algorithm
//
// content : Time Complexity O(N^2)
//
// content : Function std::exp
//
// content : Fast Fourier Transform Algorithm
//
// content : Cooley-Tukey Algorithm
//
// content : Time Complexity O(N*log(N))

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

auto transform_v1(signal_t const & X)
{
    auto size = std::size(X);

    signal_t Y(size, signal_t::value_type(0));

    for (auto i = 0uz; i < size; ++i) 
    {
        for (auto j = 0uz; j < size; ++j) 
        {
            Y[i] += X[j] * std::exp(-2i * (std::numbers::pi * i * j / size));
        }
    }

    return Y;
}

///////////////////////////////////////////////////////////////////////////////////////

auto transform_v2(signal_t const & X) -> signal_t
{
    if (auto size = std::size(X), half = size / 2; size > 1)
    {
        signal_t E(half, 0);

        signal_t O(half, 0);

        for (auto i = 0uz; 2 * i < size; ++i)
        {
            E[i] = X[2 * i + 0];

            O[i] = X[2 * i + 1];
        }

        E = transform_v2(E);

        O = transform_v2(O);

        signal_t Y(size, 0);

        signal_t::value_type w = 1;

        auto angle = 2 * std::numbers::pi / size;

        for (auto i = 0uz; 2 * i < size; ++i)
        {
            Y[i       ] = E[i] + w * O[i];

            Y[i + half] = E[i] - w * O[i];

            w *= signal_t::value_type(std::cos(angle), std::sin(angle));
        }

        return Y;
    }
    else
    {
        return X;
    }
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
    signal_t X = { 0.0 + 0.0i, 0.0 + 1.0i, 1.0 + 0.0i, 1.0 + 1.0i };

//  ----------------------------------------------------------------

    auto Y = transform_v1(X);

    auto Z = transform_v2(X);

//  ----------------------------------------------------------------

    for (auto i = 0uz; i < std::size(X); ++i)
    {
        assert(equal(Y[i], Z[i]));
    }
}

///////////////////////////////////////////////////////////////////////////////////////