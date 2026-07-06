/////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

/////////////////////////////////////////////////////////////////////////////////////////////////

// content : Inter-Process Communication (IPC)
//
// content : Library Boost.Interpocess
//
// content : Shared Memory
//
// content : Shared Memory Mappings
//
// content : Algorithms std::ranges::fill_n and std::ranges::for_each_n
//
// content : Memory Mapped Files

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iterator>

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <sys/wait.h>
#include <unistd.h>

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using shared_memory_t = boost::interprocess::shared_memory_object;

//  ---------------------------------------------------------------------------------------------

	auto path = "output";

//  ---------------------------------------------------------------------------------------------

    boost::interprocess::shared_memory_object::remove(path);

//  ---------------------------------------------------------------------------------------------

    auto mode = boost::interprocess::read_write;

//  ---------------------------------------------------------------------------------------------

    shared_memory_t storage(boost::interprocess::create_only, path, mode);

//  ---------------------------------------------------------------------------------------------

    storage.truncate(1 << 10);

//  ---------------------------------------------------------------------------------------------

    boost::interprocess::mapped_region mapping(storage, mode);

//  ---------------------------------------------------------------------------------------------

    std::ranges::fill_n(static_cast < char * > (mapping.get_address()), 1 << 10, 'a');

//  ---------------------------------------------------------------------------------------------

    if (auto id = fork(); id != 0)
    {
        wait(nullptr);

    //  --------------------------------------------------------

        boost::interprocess::shared_memory_object::remove(path);
    }
    else
    {
        auto mode = boost::interprocess::read_only;

    //  -----------------------------------------------------------------------------------------

        shared_memory_t storage(boost::interprocess::open_only, path, mode);

    //  -----------------------------------------------------------------------------------------

        boost::interprocess::mapped_region mapping(storage, mode);

    //  -----------------------------------------------------------------------------------------

        auto lambda = [](auto x) static { assert(x == 'a'); };

    //  -----------------------------------------------------------------------------------------

        std::ranges::for_each_n(static_cast < char * > (mapping.get_address()), 1 << 10, lambda);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////