#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <limits>

int main()
{
    constexpr auto epsilon = 0.000001;

    constexpr std::complex < double > complex(0.0, 1.0);

    std::cout << complex << std::endl; // note: outputs (0.0, 1.0)

    assert(std::abs(complex.real() - 0.0) < epsilon);
    assert(std::abs(complex.imag() - 1.0) < epsilon);

    std::cout << (complex + complex) << std::endl; // note: outputs ( 0.0, 2.0)
    std::cout << (complex - complex) << std::endl; // note: outputs ( 0.0, 0.0)
    std::cout << (complex * complex) << std::endl; // note: outputs (-1.0, 0.0)
    std::cout << (complex / complex) << std::endl; // note: outputs ( 1.0, 0.0)

    assert(std::abs(std::abs (complex) - 1.000000) < epsilon);
    assert(std::abs(std::norm(complex) - 1.000000) < epsilon);

    std::cout << std::conj (complex) << std::endl; // note: outputs (0.0, -1.0)
    std::cout << std::proj (complex) << std::endl; // note: outputs (0.0,  1.0)

    decltype(complex)::value_type r = 1.0, t = 0.8;

    std::cout << std::polar(r      ) << std::endl; // note: outputs (1.000000, 0.000000)
    std::cout << std::polar(r, t   ) << std::endl; // note: outputs (0.696707, 0.717356)

    std::cout << std::exp  (complex) << std::endl; // note: outputs (0.540302, 0.841471)
    std::cout << std::log  (complex) << std::endl; // note: outputs (0.000000, 1.570800)
    std::cout << std::sqrt (complex) << std::endl; // note: outputs (0.707107, 0.707107)

    return 0;
}