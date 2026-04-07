////////////////////////////////////////////////////////////////////////////////

// chapter : Containers

////////////////////////////////////////////////////////////////////////////////

// section : Nested Containers

////////////////////////////////////////////////////////////////////////////////

// content : Matrices
//
// content : Library Boost.UBLAS
//
// content : Multiplication
//
// content : Microbenchmarking

////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <random>

////////////////////////////////////////////////////////////////////////////////

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

////////////////////////////////////////////////////////////////////////////////

auto multiply
(
    boost::numeric::ublas::matrix < double > const & A,

    boost::numeric::ublas::matrix < double > const & B
)
-> boost::numeric::ublas::matrix < double >
{
    if (auto size = A.size1(); size > 64)
    {
        auto step = size / 2;

        boost::numeric::ublas::range range_1(   0, step);
        
        boost::numeric::ublas::range range_2(step, size);

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

        boost::numeric::ublas::matrix < double > C(size, size);

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
    boost::numeric::ublas::matrix < double > matrix(size, size);

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

void test_v1(benchmark::State & state)
{
    auto argument = state.range(0);

    auto matrix_1 = make_matrix(argument);
    
    auto matrix_2 = matrix_1;

    boost::numeric::ublas::matrix < double > matrix_3(argument, argument);

    for (auto element : state)
    {
        matrix_3 = boost::numeric::ublas::prod(matrix_1, matrix_2);

		benchmark::DoNotOptimize(matrix_3);
    }
}

////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    auto argument = state.range(0);

    auto matrix_1 = make_matrix(argument);
    
    auto matrix_2 = matrix_1;

    boost::numeric::ublas::matrix < double > matrix_3(argument, argument);

    for (auto element : state)
    {
        matrix_3 = multiply(matrix_1, matrix_2);

		benchmark::DoNotOptimize(matrix_3);
    }
}

////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1)->Arg(2 << 10);

BENCHMARK(test_v2)->Arg(2 << 10);

////////////////////////////////////////////////////////////////////////////////

int main()
{
	benchmark::RunSpecifiedBenchmarks();
}

////////////////////////////////////////////////////////////////////////////////