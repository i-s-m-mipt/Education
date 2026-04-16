////////////////////////////////////////////////////////////////////////////////

// chapter : Containers

////////////////////////////////////////////////////////////////////////////////

// section : Nested Containers

////////////////////////////////////////////////////////////////////////////////

// content : Matrices
//
// content : Library Boost.UBLAS
//
// content : Strassen Fast Multiplication Algorithm
//
// content : Time Complexity O(N^2.807)

////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <cstddef>
#include <random>

////////////////////////////////////////////////////////////////////////////////

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

////////////////////////////////////////////////////////////////////////////////

using matrix_t = boost::numeric::ublas::matrix < double > ;

////////////////////////////////////////////////////////////////////////////////

auto multiply(matrix_t const & A, matrix_t const & B) -> matrix_t
{
    if (auto size = A.size1(), half = size / 2; size > 64)
    {
        boost::numeric::ublas::range range_1(   0, half);
        
        boost::numeric::ublas::range range_2(half, size);

        auto A11 = boost::numeric::ublas::project(A, range_1, range_1);

        auto A12 = boost::numeric::ublas::project(A, range_1, range_2);

        auto A21 = boost::numeric::ublas::project(A, range_2, range_1);

        auto A22 = boost::numeric::ublas::project(A, range_2, range_2);

        auto B11 = boost::numeric::ublas::project(B, range_1, range_1);

        auto B12 = boost::numeric::ublas::project(B, range_1, range_2);

        auto B21 = boost::numeric::ublas::project(B, range_2, range_1);

        auto B22 = boost::numeric::ublas::project(B, range_2, range_2);

        auto C1 = multiply(A11 + A22, B11 + B22);

        auto C2 = multiply(A11 + A12, B22), C3 = multiply(A11, B12 - B22);

        auto C4 = multiply(A21 + A22, B11), C5 = multiply(A22, B21 - B11);

        auto C6 = multiply(A21 - A11, B11 + B12);

        auto C7 = multiply(A12 - A22, B21 + B22);

        matrix_t C(size, size);

        boost::numeric::ublas::project(C, range_1, range_1) = C1 - C2 + C5 + C7;

        boost::numeric::ublas::project(C, range_1, range_2) = C2 + C3;

        boost::numeric::ublas::project(C, range_2, range_1) = C4 + C5;

        boost::numeric::ublas::project(C, range_2, range_2) = C1 + C3 - C4 + C6;

        return C;
    }
    else
    {
        return boost::numeric::ublas::prod(A, B);
    }
}

////////////////////////////////////////////////////////////////////////////////

auto make_matrix(std::size_t size)
{
    matrix_t matrix(size, size);

    std::uniform_real_distribution distribution(0.0, 1.0);

    std::default_random_engine engine;

    for (auto i = 0uz; i < matrix.size1(); ++i)
    {
        for (auto j = 0uz; j < matrix.size2(); ++j)
        {
            matrix(i, j) = distribution(engine);
        }
    }

    return matrix;
}

////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto size = 1uz << 10;

//  --------------------------------------------

	auto A = make_matrix(size), B = A;

//  --------------------------------------------

    auto C1 = boost::numeric::ublas::prod(A, B);

    auto C2 = multiply(A, B);

//  --------------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        for (auto j = 0uz; j < size; ++j)
        {
            assert(equal(C1(i, j), C2(i, j)));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////