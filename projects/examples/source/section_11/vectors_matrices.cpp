#include <cassert>
#include <exception>
#include <random>
#include <stdexcept>

//#define BOOST_UBLAS_TYPE_CHECK 0 // bad: for integral types

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <benchmark/benchmark.h>

double determinant_v1(const boost::numeric::ublas::matrix < double > & matrix) // good: for small
{
    if (const auto size = matrix.size1(); size == matrix.size2() && size != 0)
    {
        if (size == 1) return matrix(0, 0); else
        {
            auto determinant = 0.0;
    
            for (std::size_t i = 0; i < size; ++i) 
            {
                boost::numeric::ublas::matrix < double > minor(size - 1, size - 1);

                for (std::size_t j = 1; j < size; ++j) 
                {
                    for (std::size_t k = 0, c = 0; k < size; ++k) 
                    {
                        if (k != i) minor(j - 1, c++) = matrix(j, k);
                    }
                }

                determinant += (i % 2 ? -1.0 : +1.0) * matrix(0, i) * determinant_v1(minor);
            }

            return determinant;
        }
    }
    else throw std::runtime_error("invalid matrix");
}

double determinant_v2(const boost::numeric::ublas::matrix < double > & matrix) // good: for big
{    
    if (const auto size = matrix.size1(); size == matrix.size2() && size != 0)
    {
        if (size == 1) return matrix(0, 0); else
        {
            boost::numeric::ublas::matrix < double > copy(matrix);
    
            boost::numeric::ublas::permutation_matrix <> permutation(size);

            if (!boost::numeric::ublas::lu_factorize(copy, permutation)) // note: check singularity
            {
                auto determinant = 1.0;

                for (std::size_t i = 0; i < copy.size1(); ++i)
                {
                    if (permutation(i) != i) determinant *= -1.0;

                    determinant *= copy(i, i);
                }

                return determinant;
            }
            else return 0.0;
        }
    }
    else throw std::runtime_error("invalid matrix");
}

boost::numeric::ublas::matrix < double > make_random_matrix(std::size_t size)
{
    boost::numeric::ublas::matrix < double > matrix(size, size);

    std::mt19937 engine(42);

    std::uniform_real_distribution distribution(0.0, 10.0);

    for (std::size_t i = 0; i < matrix.size1(); ++i)
    {
        for (std::size_t j = 0; j < matrix.size2(); ++j)
        {
            matrix(i, j) = distribution(engine);
        }
    }

    return matrix;
}

void test_1(benchmark::State & state) // note: better for 3x3 or less
{
    auto matrix = make_random_matrix(state.range(0));

    for (auto _ : state)
    {
        auto determinant = determinant_v1(matrix);

		benchmark::DoNotOptimize(determinant);	
    }
}

void test_2(benchmark::State & state) // note: better for 4x4 or more
{
    auto matrix = make_random_matrix(state.range(0));

    for (auto _ : state)
    {
        auto determinant = determinant_v2(matrix);

		benchmark::DoNotOptimize(determinant);	
    }
}

BENCHMARK(test_1)->DenseRange(1, 9, 1); 
BENCHMARK(test_2)->DenseRange(1, 9, 1);  

int main(int argc, char ** argv) // note: arguments for benchmark
{
    auto matrix = make_random_matrix(3);

    const auto epsilon = 0.001;

    assert(std::abs(determinant_v1(matrix) - 12.595) < epsilon);
    assert(std::abs(determinant_v2(matrix) - 12.595) < epsilon);

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}