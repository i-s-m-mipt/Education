#include <cassert>

#include <boost/pool/object_pool.hpp>

////////////////////////////////////////

int main()
{
    boost::object_pool < int > pool(32);

//  ------------------------------------

    auto ptr = pool.malloc();

    *ptr = 1;
        
    pool.destroy(ptr);

//  ------------------------------------

    assert(pool.get_next_size() == 64);
}