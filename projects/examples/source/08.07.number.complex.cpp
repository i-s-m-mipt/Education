#include <cassert>
#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <vector>

using namespace std::literals;

//  ================================================================================================

using signal_t = std::vector < std::complex < double > > ;

//  ================================================================================================

[[nodiscard]] constexpr signal_t fourier_transform(const signal_t & signal)
{
    const auto size = std::size(signal);

    signal_t result(size);
    
    for (std::size_t i = 0; i < size; ++i) 
    {
        for (std::size_t j = 0; j < size; ++j) 
        {
            result[i] += signal[j] * std::exp(-2.0i * (std::numbers::pi * i * j / size));
        }
    }

    return result;
}

//  ================================================================================================

[[nodiscard]] constexpr signal_t generate_signal(std::size_t size)
{
    signal_t signal(size);

    for (std::size_t i = 0; i < size; ++i)
    {
        signal[i] = std::sin(2.0 * i * std::numbers::pi / size);
    }

    return signal;
}

//  ================================================================================================

void print_signal(const signal_t & signal)
{
    for (auto element : signal) 
    {
        std::cout << std::showpos << std::setprecision(3) << std::fixed << element.real() << ' ';
    }

    std::cout << std::endl;
}

//  ================================================================================================

int main()
{
    constexpr auto epsilon = 0.000001;

    constexpr std::complex < double > complex(0.0, 1.0);

    std::cout << std::showpos << std::setprecision(3) << std::fixed;

    std::cout << complex << std::endl; // note: outputs (+0.000,+1.000)

    assert(std::abs(          complex.real()  - 0.0) < epsilon);
    assert(std::abs(          complex.imag()  - 1.0) < epsilon);
    assert(std::abs(std::abs (complex       ) - 1.0) < epsilon);
    assert(std::abs(std::norm(complex       ) - 1.0) < epsilon);

//  ================================================================================================

    std::cout << (complex + complex) << std::endl; // note: outputs (+0.000,+2.000)
    std::cout << (complex - complex) << std::endl; // note: outputs (+0.000,+0.000)
    std::cout << (complex * complex) << std::endl; // note: outputs (-1.000,+0.000)
    std::cout << (complex / complex) << std::endl; // note: outputs (+1.000,+0.000)

//  ================================================================================================

    std::cout << std::conj (complex) << std::endl; // note: outputs (+0.000,-1.000)
    std::cout << std::proj (complex) << std::endl; // note: outputs (+0.000,+1.000)
    std::cout << std::exp  (complex) << std::endl; // note: outputs (+0.540,+0.841)
    std::cout << std::log  (complex) << std::endl; // note: outputs (+0.000,+1.571)
    std::cout << std::sqrt (complex) << std::endl; // note: outputs (+0.707,+0.707)

//  ================================================================================================

    decltype(complex)::value_type r = 1.0, t = 0.8;

    std::cout << std::polar(r      ) << std::endl; // note: outputs (+1.000,+0.000)
    std::cout << std::polar(r, t   ) << std::endl; // note: outputs (+0.697,+0.717)

//  ================================================================================================

    const auto signal = generate_signal(8);

    print_signal(                  signal );
    print_signal(fourier_transform(signal));

    return 0;
}