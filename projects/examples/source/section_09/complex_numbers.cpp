#include <complex>
#include <iostream>

int main()
{
    std::complex < double > c(0.0, 1.0);

    std::cout << c        << std::endl; // note: outputs (0.0, 1.0)

    std::cout << c.real() << std::endl; // note: outputs  0.0
    std::cout << c.imag() << std::endl; // note: outputs  1.0

    std::cout << c + c << std::endl; // note: outputs ( 0.0, 2.0)
    std::cout << c - c << std::endl; // note: outputs ( 0.0, 0.0)
    std::cout << c * c << std::endl; // note: outputs (-1.0, 0.0)
    std::cout << c / c << std::endl; // note: outputs ( 1.0, 0.0)

    std::cout << std::abs (c) << std::endl; // note: outputs 1.000000
    std::cout << std::arg (c) << std::endl; // note: outputs 1.570800
    std::cout << std::norm(c) << std::endl; // note: outputs 1.000000

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