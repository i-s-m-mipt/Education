#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>

//////////////////////////////////////////////////////////////////////////////////////////

auto is_even(int x) 
{
    return x % 2 == 0;
}

BOOST_AUTO_TEST_CASE(Test_v1)
{
    BOOST_TEST(is_even(1)); std::cout << "Test_v1 (1)\n";
    BOOST_TEST(is_even(2)); std::cout << "Test_v1 (2)\n";
}

//////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(Test_v2) 
{
    BOOST_TEST(1.0 == 1.0, boost::test_tools::tolerance(1e-6));

    BOOST_TEST("aaaaa" < "bbbbb", boost::test_tools::lexicographic());
} 

//////////////////////////////////////////////////////////////////////////////////////////

BOOST_DATA_TEST_CASE
(
    Test_v3, 

    boost::unit_test::data::xrange(1, 3, 1) * 
    boost::unit_test::data::xrange(1, 4, 1), 

    x, y
)
{
    std::cout << "Test_v3 : x = " << x << " y = " << y << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////////

BOOST_DATA_TEST_CASE
(
    Test_v4, 

    boost::unit_test::data::xrange(5) ^ boost::unit_test::data::random
    ((
        boost::unit_test::data::seed = std::random_device()(),
            
        boost::unit_test::data::engine = std::mt19937_64(),

        boost::unit_test::data::distribution = std::uniform_real_distribution(0.0, 1.0)
    )),

    index, sample
)
{
    std::cout << "Test_v4 : index = " << index << " sample = ";
    
    std::cout << std::setprecision(3) << std::fixed << sample << '\n';

    BOOST_TEST(sample < 0.5);
}

//////////////////////////////////////////////////////////////////////////////////////////

class Dataset 
{
public:

    class iterator
    {
    public:

        using iterator_category = std::forward_iterator_tag;

    //  ---------------------------------------------------------------

        iterator() : m_x(1), m_y(1) {}

    //  ---------------------------------------------------------------

        const auto operator++(int) 
		{ 
			auto copy(*this); 
            
            m_x += m_y; std::swap(m_x, m_y);  
            
            return copy; 
		}

        auto & operator++() 
		{ 
			m_x += m_y; std::swap(m_x, m_y); 
            
            return *this;
		}		

        auto operator*() const
        { 
            return m_y; 
        } 

		auto operator==(const iterator & other) const
		{ 
			return m_x == other.m_x && m_y == other.m_y; 
		}

    private:

        int m_x = 1;
        int m_y = 1;
    };

//  ---------------------------------------------------------------

    auto begin() const
    { 
        return iterator(); 
    }

//  ---------------------------------------------------------------

    auto size() const
    { 
        return boost::unit_test::data::BOOST_TEST_DS_INFINITE_SIZE;
    }
}; 

//////////////////////////////////////////////////////////////////////////////////////////

namespace boost::unit_test::data::monomorphic 
{
    template <> class is_dataset < Dataset > : public std::true_type {};
}

//////////////////////////////////////////////////////////////////////////////////////////

BOOST_DATA_TEST_CASE
(
    Test_v5, Dataset() ^ boost::unit_test::data::make({ 1, 2, 3, 5, 8 }), sample, expected
)
{
    BOOST_TEST(sample == expected);
}

//////////////////////////////////////////////////////////////////////////////////////////

using list_t = boost::mpl::list < bool, char, int, double > ;

BOOST_AUTO_TEST_CASE_TEMPLATE(Test_v6, T, list_t)
{
    BOOST_TEST(sizeof(T) == 4);
}

//////////////////////////////////////////////////////////////////////////////////////////

void test(int x)
{
    BOOST_TEST(x < 5);
}

boost::unit_test::test_suite * init_unit_test_suite(int, char **)
{
    std::vector < int > vector { 1, 2, 3, 4, 5 };

    auto test_case = BOOST_PARAM_TEST_CASE(&test, std::begin(vector), std::end(vector));

    boost::unit_test::framework::master_test_suite().add(test_case);

    boost::unit_test::framework::master_test_suite().p_name.value = "master";

    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////

class Fixture
{
public:

    std::vector < int > data;
};

//////////////////////////////////////////////////////////////////////////////////////////

BOOST_FIXTURE_TEST_CASE(Test_v7, Fixture)
{
    BOOST_TEST(std::size(data), 0); data.push_back(1);
    BOOST_TEST(std::size(data), 1); data.push_back(2);
    BOOST_TEST(std::size(data), 2);
}