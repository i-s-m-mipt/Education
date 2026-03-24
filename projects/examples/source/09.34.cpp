/////////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

/////////////////////////////////////////////////////////////////////////////////////

// section : Advanced Allocators

/////////////////////////////////////////////////////////////////////////////////////

// content : Polymorphic Resources and Allocators
//
// content : Resource std::pmr::monotonic_buffer_resource
//
// content : Function std::data
//
// content : Allocator std::pmr::polymorphic_allocator
//
// content : Container std::pmr::vector

/////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cassert>
#include <cstddef>
#include <memory_resource>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::array < std::byte, 1'024 > array = {};

//  ---------------------------------------------------------------------------------

    std::pmr::monotonic_buffer_resource resource(std::data(array), std::size(array));

//  ---------------------------------------------------------------------------------

    std::pmr::polymorphic_allocator < int > allocator(&resource);

//  ---------------------------------------------------------------------------------

    std::pmr::vector < int > vector(allocator);

//  ---------------------------------------------------------------------------------

    vector = { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------------------------------------

    auto index = 0uz;

//  ---------------------------------------------------------------------------------

    for (auto i = 0uz; i < std::size(vector); ++i, index += sizeof(int))
    {
        assert(std::to_integer < int > (array[index]) == vector[i]);
    }

//  ---------------------------------------------------------------------------------

    vector.push_back(1);

//  ---------------------------------------------------------------------------------

    for (auto i = 0uz; i < std::size(vector); ++i, index += sizeof(int))
    {
        assert(std::to_integer < int > (array[index]) == vector[i]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////