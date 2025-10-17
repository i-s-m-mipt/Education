////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <format>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/list.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/data/size.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/tree/test_unit.hpp>
#include <boost/test/unit_test_suite.hpp>

////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(Test_v1)
{
    std::cout << "Test_v1\n"; BOOST_TEST(std::max(1, 2) == 1);

    std::cout << "Test_v1\n"; BOOST_TEST(std::max(1, 2) == 2);
}

////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(Test_v2) 
{
    BOOST_TEST(1e-9 == 2e-9, boost::test_tools::tolerance(1e-6));
}

////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(Test_v3) 
{
    BOOST_TEST("aaaaa" < "bbbbb", boost::test_tools::lexicographic());
}

////////////////////////////////////////////////////////////////////////////////////////

BOOST_DATA_TEST_CASE
(
    Test_v4, 

    boost::unit_test::data::xrange(1, 3, 1) * boost::unit_test::data::xrange(1, 4, 1),

    x, y
)
{
    std::cout << "Test_v3 : x = " << x << " y = " << y << '\n';

    BOOST_TEST(x > 0); BOOST_TEST(x < 3);

    BOOST_TEST(y > 0); BOOST_TEST(y < 4);
}

////////////////////////////////////////////////////////////////////////////////////////

BOOST_DATA_TEST_CASE
(
    Test_v5, 

    boost::unit_test::data::xrange(5) ^ boost::unit_test::data::random
    ((   
        boost::unit_test::data::distribution = std::uniform_real_distribution(0.0, 1.0),

        boost::unit_test::data::seed = 1,

        boost::unit_test::data::engine = std::default_random_engine()
    )),

    i, x
)
{
    std::cout << "Test_v4 : i = " << i << " x = " << std::format("{:.3f}", x) << '\n';

    BOOST_TEST(x > 0.5);
}

////////////////////////////////////////////////////////////////////////////////////////

class Dataset 
{
public :

    class iterator
    {
    public :

        iterator() : m_x(1), m_y(1) {}

    //  ------------------------------------------------------------------

        auto const operator++(int) 
        { 
            auto x = *this;
            
            m_x += m_y;
            
            std::swap(m_x, m_y);
            
            return x;
        }

    //  ------------------------------------------------------------------

        auto & operator++() 
        { 
            m_x += m_y;
            
            std::swap(m_x, m_y);
            
            return *this;
        }
        
    //  ------------------------------------------------------------------

        auto operator*() const
        { 
            return m_y;
        }

    //  ------------------------------------------------------------------

		friend auto operator==(iterator const & lhs, iterator const & rhs)
		{ 
			return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
		}

    private :

        int m_x = 1, m_y = 1;
    };

//  ----------------------------------------------------------------------

    auto begin() const
    { 
        return iterator();
    }

//  ----------------------------------------------------------------------

    auto size() const
    { 
        return boost::unit_test::data::BOOST_TEST_DS_INFINITE_SIZE;
    }
};

////////////////////////////////////////////////////////////////////////////////////////

namespace boost::unit_test::data::monomorphic 
{
    template <> class is_dataset < Dataset > : public std::true_type {};
}

////////////////////////////////////////////////////////////////////////////////////////

BOOST_DATA_TEST_CASE
(
    Test_v6, Dataset() ^ boost::unit_test::data::make({ 1, 2, 3, 5, 8 }), x, y
)
{
    BOOST_TEST(x == y);
}

////////////////////////////////////////////////////////////////////////////////////////

using list_t = boost::mpl::list < int, std::string > ;

////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE_TEMPLATE(Test_v7, T, list_t)
{
    BOOST_TEST(sizeof(T) == 4);
}

////////////////////////////////////////////////////////////////////////////////////////

void test(int x)
{
    BOOST_TEST(x > 0);
}

////////////////////////////////////////////////////////////////////////////////////////

boost::unit_test::test_suite * init_unit_test_suite(int, char **)
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

    auto generator = BOOST_PARAM_TEST_CASE(&test, std::begin(vector), std::end(vector));

    boost::unit_test::framework::master_test_suite().add(generator);

    boost::unit_test::framework::master_test_suite().p_name.value = "master";

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////

class Fixture
{
public :

    std::vector < int > vector;
};

////////////////////////////////////////////////////////////////////////////////////////

BOOST_FIXTURE_TEST_CASE(Test_v8, Fixture)
{
    vector.push_back(1); BOOST_TEST(std::size(vector) == 1);
    
    vector.push_back(1); BOOST_TEST(std::size(vector) == 2);
}

////////////////////////////////////////////////////////////////////////////////////////