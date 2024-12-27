#include <cassert>
#include <cmath>
#include <cstddef>
#include <exception>
#include <random>
#include <stdexcept>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <benchmark/benchmark.h>

//  ================================================================================================

auto determinant_v1(const boost::numeric::ublas::matrix < double > & matrix) -> double
{
    if (auto size = matrix.size1(); size == matrix.size2() && size != 0)
    {
        if (size > 1)
        {
            auto determinant = 0.0;
    
            for (auto i = 0uz; i < size; ++i) 
            {
                boost::numeric::ublas::matrix < double > minor(size - 1, size - 1);

                for (auto j = 1uz; j < size; ++j) 
                {
                    for (auto k = 0uz, c = 0uz; k < size; ++k) 
                    {
                        if (k != i) 
                        {
                            minor(j - 1, c++) = matrix(j, k);
                        }
                    }
                }

                determinant += (i % 2 ? -1.0 : +1.0) * matrix(0, i) * determinant_v1(minor);
            }

            return determinant;
        }
        else
        {
            return matrix(0, 0);
        }
    }
    else 
    {
        throw std::runtime_error("invalid size");
    }
}

//  ================================================================================================

auto determinant_v2(const boost::numeric::ublas::matrix < double > & matrix)
{    
    if (auto size = matrix.size1(); size == matrix.size2() && size != 0)
    {
        if (size > 1)
        {
            boost::numeric::ublas::matrix < double > copy(matrix);
    
            boost::numeric::ublas::permutation_matrix <> permutation(size);

            if (!boost::numeric::ublas::lu_factorize(copy, permutation))
            {
                auto determinant = 1.0;

                for (auto i = 0uz; i < copy.size1(); ++i)
                {
                    if (permutation(i) != i) 
                    {
                        determinant *= -1.0;
                    }

                    determinant *= copy(i, i);
                }

                return determinant;
            }
            else 
            {
                return 0.0;
            }
        }
        else
        {
            return matrix(0, 0);
        }
    }
    else 
    {
        throw std::runtime_error("invalid size");
    }
}

//  ================================================================================================

auto make_matrix(std::size_t size)
{
    boost::numeric::ublas::matrix < double > matrix(size, size);

    std::default_random_engine engine;

    std::uniform_real_distribution distribution(0.0, 1.0);

    for (auto i = 0uz; i < matrix.size1(); ++i)
    {
        for (auto j = 0uz; j < matrix.size2(); ++j)
        {
            matrix(i, j) = distribution(engine);
        }
    }

    return matrix;
}

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

void test_v1(benchmark::State & state)
{
    auto matrix = make_matrix(state.range(0));

    for (auto value : state)
    {
		benchmark::DoNotOptimize(determinant_v1(matrix));	
    }
}

//  ================================================================================================

void test_v2(benchmark::State & state)
{
    auto matrix = make_matrix(state.range(0));
    
    for (auto value : state)
    {
		benchmark::DoNotOptimize(determinant_v2(matrix));	
    }
}

//  ================================================================================================

BENCHMARK(test_v1)->DenseRange(1, 9, 1); 
BENCHMARK(test_v2)->DenseRange(1, 9, 1);  

//  ================================================================================================

int main()
{
    auto matrix = make_matrix(3);

    assert
    (
        equal
        (
            determinant_v1(matrix), 
            determinant_v2(matrix)
        )
    );

	benchmark::RunSpecifiedBenchmarks();
}