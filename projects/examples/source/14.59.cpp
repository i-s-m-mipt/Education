/////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

/////////////////////////////////////////////////////////////////////////////

// content : Managed Shared Memory Allocators

/////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iterator>

/////////////////////////////////////////////////////////////////////////////

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

/////////////////////////////////////////////////////////////////////////////

int main()
{
    using shared_memory_t = boost::interprocess::managed_shared_memory;

//  -------------------------------------------------------------------------

	auto path = "output";

//  -------------------------------------------------------------------------

	boost::interprocess::shared_memory_object::remove(path);

//  -------------------------------------------------------------------------

	shared_memory_t storage(boost::interprocess::create_only, path, 1 << 10);

//  -------------------------------------------------------------------------

	using vector_t = boost::interprocess::vector
    <
        int,

        boost::interprocess::allocator
        <
            int, boost::interprocess::managed_shared_memory::segment_manager
        >
    > ;

//  -------------------------------------------------------------------------

	storage.construct < vector_t > ("vector")(storage.get_segment_manager());

//  -------------------------------------------------------------------------

    auto [vector, unused] = storage.find < vector_t > ("vector");

//  -------------------------------------------------------------------------

    vector->push_back(1);

//  -------------------------------------------------------------------------

    assert(std::size(*vector) == 1 && vector->at(0) == 1);

//  -------------------------------------------------------------------------

    storage.destroy < vector_t > ("vector");

//  -------------------------------------------------------------------------

	boost::interprocess::shared_memory_object::remove(path);
}

/////////////////////////////////////////////////////////////////////////////