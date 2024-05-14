#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>

#define BOOST_TEST_MODULE boost_testing

#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>

//  ================================================================================================

[[nodiscard]] inline constexpr int factorial(int n) noexcept 
{ 
    return (n < 2 ? 1 : n * factorial(n - 1)); 
}

BOOST_AUTO_TEST_CASE(factorial_test)
{
    BOOST_TEST(factorial(0) ==     1);
    BOOST_TEST(factorial(1) ==     1);
    BOOST_TEST(factorial(2) ==     2);
    BOOST_TEST(factorial(3) ==     6);
    BOOST_TEST(factorial(5) ==   120);
    BOOST_TEST(factorial(8) == 40320);

    BOOST_TEST(factorial(4) ==    25);
}

//  ================================================================================================

BOOST_AUTO_TEST_CASE(expectations_test) 
{
    BOOST_TEST("aaa" < "bbb", boost::test_tools::lexicographic());

    BOOST_TEST(3.14 == 3.14,  boost::test_tools::tolerance(0.001));
} 

//  ================================================================================================

BOOST_DATA_TEST_CASE(ranges_test, boost::unit_test::data::xrange(1, 3, 1) * 
                                  boost::unit_test::data::xrange(1, 4, 1), value_1, value_2)
{
    std::cout << value_1 << " x " << value_2 << std::endl;
}

BOOST_DATA_TEST_CASE(random_test, (boost::unit_test::data::random((

    boost::unit_test::data::seed         = std::random_device{}(),
    boost::unit_test::data::engine       = std::mt19937_64     (),
    boost::unit_test::data::distribution = std::uniform_real_distribution(0.0, 1.0))) ^ 
    
    boost::unit_test::data::xrange(10)), sample, index)
{
    std::cout << index << " : " << std::setprecision(3) << std::fixed << sample << std::endl;

    BOOST_TEST(sample < 0.7);
}

//  ================================================================================================

class Dataset 
{
public:

    class iterator
    {
    public:

        using iterator_category = std::forward_iterator_tag;

        constexpr iterator() noexcept : m_x(1), m_y(1) {}

    public:

        constexpr iterator & operator++() noexcept 
		{ 
			m_x += m_y; std::swap(m_x, m_y); return *this;
		}

		constexpr iterator operator++(int) noexcept 
		{ 
			auto previous = *this; ++(*this); return previous; 
		}

        [[nodiscard]] constexpr int operator*() const noexcept
        { 
            return m_y; 
        } 

		[[nodiscard]] constexpr bool operator==(const iterator & other) const noexcept 
		{ 
			return (m_x == other.m_x && m_y == other.m_y); 
		}

    private:

        int m_x, m_y;

    }; // class iterator 

    [[nodiscard]] constexpr iterator begin() const noexcept { return iterator(); }

    [[nodiscard]] boost::unit_test::data::size_t size() const noexcept 
    { 
        return boost::unit_test::data::BOOST_TEST_DS_INFINITE_SIZE;
    }

    static constexpr auto arity = 1;

}; // class Dataset 

//  ================================================================================================

namespace boost::unit_test::data::monomorphic 
{
    template <> struct is_dataset < Dataset > : std::true_type {};
}

//  ================================================================================================

BOOST_DATA_TEST_CASE(fibonacci_test, Dataset() ^ boost::unit_test::data::make( { 1, 2, 3, 5, 9 } ), sample, expected)
{
    BOOST_TEST(sample == expected);
}

//  ================================================================================================

using test_types = boost::mpl::list < bool, char, int, double > ;

BOOST_AUTO_TEST_CASE_TEMPLATE(template_test, T, test_types) // support: static_assert
{
    BOOST_TEST(sizeof(T) == 4);
}

//  ================================================================================================

void free_test_function(int parameter)
{
    BOOST_TEST(parameter < 4);
}

boost::unit_test::test_suite * init_unit_test_suite(int, char**)
{
    const std::vector < int > parameters { 1, 2, 3, 4, 5 };

    const auto test_case = BOOST_PARAM_TEST_CASE(&free_test_function, std::cbegin(parameters), 
                                                                      std::cend  (parameters));

    boost::unit_test::framework::master_test_suite().add(test_case);

    boost::unit_test::framework::master_test_suite().p_name.value = "master";

    return nullptr;
}

//  ================================================================================================

class Fixture
{
public:

    Fixture() { BOOST_TEST_MESSAGE("Fixture:: Fixture"); }
   ~Fixture() { BOOST_TEST_MESSAGE("Fixture::~Fixture"); } 

public:

    std::vector < int > data;

}; // class Fixture

BOOST_FIXTURE_TEST_CASE(fixture_test, Fixture)
{
    BOOST_TEST(std::size(data) == 0); data.push_back(42);
    BOOST_TEST(std::size(data) == 1); data.push_back(42);
    BOOST_TEST(std::size(data) == 2);
}