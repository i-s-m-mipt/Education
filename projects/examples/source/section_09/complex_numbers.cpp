#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <limits>

int main()
{
    const auto epsilon = 0.000001;

    std::complex < double > c(0.0, 1.0);

    std::cout << c << std::endl; // note: outputs (0.0, 1.0)

    assert(std::abs(c.real() - 0.0) < epsilon);
    assert(std::abs(c.imag() - 1.0) < epsilon);

    std::cout << c + c << std::endl; // note: outputs ( 0.0, 2.0)
    std::cout << c - c << std::endl; // note: outputs ( 0.0, 0.0)
    std::cout << c * c << std::endl; // note: outputs (-1.0, 0.0)
    std::cout << c / c << std::endl; // note: outputs ( 1.0, 0.0)

    assert(std::abs(std::abs (c) - 1.000000) < epsilon);
    assert(std::abs(std::norm(c) - 1.000000) < epsilon);

    std::cout << std::conj(c) << std::endl; // note: outputs (0.0, -1.0)
    std::cout << std::proj(c) << std::endl; // note: outputs (0.0,  1.0)

    decltype(c)::value_type r = 1.0;
    decltype(c)::value_type t = 0.8;

    std::cout << std::polar(r   ) << std::endl; // note: outputs (1.000000, 0.000000)
    std::cout << std::polar(r, t) << std::endl; // note: outputs (0.696707, 0.717356)

    std::cout << std::exp  (c   ) << std::endl; // note: outputs (0.540302, 0.841471)
    std::cout << std::log  (c   ) << std::endl; // note: outputs (0.000000, 1.570800)
    std::cout << std::pow  (c, c) << std::endl; // note: outputs (0.207880, 0.000000)
    std::cout << std::sqrt (c   ) << std::endl; // note: outputs (0.707107, 0.707107)

    return 0;
}