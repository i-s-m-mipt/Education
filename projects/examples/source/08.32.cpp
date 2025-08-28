////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>

////////////////////////////////////////////////////////////////////////////

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>
#include <boost/accumulators/statistics/weighted_variance.hpp>

////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////////////////

int main()
{
    using features_t = boost::accumulators::features
    <
        boost::accumulators::tag::weighted_mean,

        boost::accumulators::tag::weighted_variance
    > ;

//  ------------------------------------------------------------------------

    boost::accumulators::accumulator_set < double, features_t, double > set;

//  ------------------------------------------------------------------------

    for (auto i = 1; i <= 5; ++i)
    {
        set(i, boost::accumulators::weight = i);
    }

//  ------------------------------------------------------------------------

    assert(equal(boost::accumulators::weighted_mean    (set), 3.666'666));

    assert(equal(boost::accumulators::weighted_variance(set), 1.555'555));
}

////////////////////////////////////////////////////////////////////////////