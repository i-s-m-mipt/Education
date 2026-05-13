////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

////////////////////////////////////////////////////////////////////////////////////////////

// section : Processes

////////////////////////////////////////////////////////////////////////////////////////////

// content : Inter-Process Communication (IPC)
//
// content : Shared Memory
//
// content : Library Boost.Interpocess
//
// content : Memory Mapped Files

////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

////////////////////////////////////////////////////////////////////////////////////////////

#include <sys/wait.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto path = "output";

//  ----------------------------------------------------------------------------------------

    boost::interprocess::shared_memory_object::remove(path);

//  ----------------------------------------------------------------------------------------

    boost::interprocess::shared_memory_object storage
    (
        boost::interprocess::create_only, path, boost::interprocess::read_write
    );

//  ----------------------------------------------------------------------------------------

    storage.truncate(1 << 10);

//  ----------------------------------------------------------------------------------------

    boost::interprocess::mapped_region mapping(storage, boost::interprocess::read_write);

//  ----------------------------------------------------------------------------------------

    auto begin = static_cast < char * > (mapping.get_address());

//  ----------------------------------------------------------------------------------------

    std::ranges::fill(begin, std::next(begin, mapping.get_size()), 'a');

//  ----------------------------------------------------------------------------------------

    if (auto id = fork(); id != 0)
    {
        wait(nullptr);

    //  --------------------------------------------------------

        boost::interprocess::shared_memory_object::remove(path);
    }
    else
    {
        boost::interprocess::shared_memory_object storage
        (
		    boost::interprocess::open_only, path, boost::interprocess::read_only
        );

    //  ------------------------------------------------------------------------------------

        boost::interprocess::mapped_region mapping(storage, boost::interprocess::read_only);

    //  ------------------------------------------------------------------------------------

        begin = static_cast < char * > (mapping.get_address());

    //  ------------------------------------------------------------------------------------

        auto lambda = [](auto x){ assert(x == 'a'); };

    //  ------------------------------------------------------------------------------------

        std::ranges::for_each(begin, std::next(begin, mapping.get_size()), lambda);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////