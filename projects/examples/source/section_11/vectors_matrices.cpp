#include <iostream>
#include <vector>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/

int main(int argc, char const *argv[])
{

    /* Векторы */

    using         array_t = std::vector < double >;
    using        vector_t = boost::numeric::ublas::vector < double, array_t >;
    using   unit_vector_t = boost::numeric::ublas::unit_vector < double >;
    using   zero_vector_t = boost::numeric::ublas::zero_vector < double >;
    using scalar_vector_t = boost::numeric::ublas::scalar_vector < double >;

    const size_t n = 4;

    vector_t vector(n, {1, 2, 4, 5});                       // Обычный вектор
    std::cout << vector << std::endl;

    unit_vector_t unit_vector (n, 2);                       // Единичный вектор (v_i = 1, v_{0..n}\i = 0)
    std::cout << unit_vector << std::endl;

    zero_vector_t zero_vector(n);                           // Нулевой вектор (the same as {0, 0, 0, 0})
    scalar_vector_t scalar_vector(n);                       // Числовой вектор (the same as {1, 1, 1, 1})

    vector(3) = 3;                                          // Возвращает ссылку на i-й элемент:
                                                            //   "With some compilers, this
                                                            //    notation will be faster than [i]."
    std::cout <<                                           
          1.5 * vector                                      // Мат. операции со скалярами
        -   4 * unit_vector
        + 0.5 * scalar_vector
    << std::endl;


    /* Векторные посредники (Vector Proxies) */

    using vector_range_t = boost::numeric::ublas::vector_range < vector_t >;
    using        range_t = boost::numeric::ublas::range;
    using vector_slice_t = boost::numeric::ublas::vector_slice < vector_t >;
    using        slice_t = boost::numeric::ublas::slice;
    using                  boost::numeric::ublas::project;
        
    vector_range_t vector_range(vector, range_t(0, 2));     // Диапазон вектора, задаётся range(start, stop)
    std::cout << vector_range << "\nthe same as subrange:\n"
    << subrange(vector, 0, 2) << std::endl;                 // Эквивалентный способ с помощью прототипа subrange

    vector_slice_t vector_slice (vector, slice_t(1, 2, 2)); // Срез вектора, задаётся slice(start, step, count)
    std::cout << vector_slice << "\nthe same as subslice:\n"
    << subslice(vector, 1, 2, 2) << std::endl;              // Эквивалентный способ с помощью прототипа subslice


    /* Матрицы */



    return 0;
}