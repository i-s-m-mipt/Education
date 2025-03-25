#include <cassert>

#include <boost/pool/object_pool.hpp>

////////////////////////////////////////

int main()
{
    boost::object_pool < int > pool(32);

//  ------------------------------------

    auto x = pool.malloc();

    *x = 1;
        
    pool.destroy(x);

//  ------------------------------------

    assert(pool.get_next_size() == 64);
}