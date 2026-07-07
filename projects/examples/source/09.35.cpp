///////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////////////////////////////////////////////////////////

// content : Polymorphic Resources and Allocators
//
// content : Resource std::pmr::monotonic_buffer_resource
//
// content : Upstream Resources
//
// content : Function std::pmr::new_delete_resource
//
// content : Allocator std::pmr::polymorphic_allocator
//
// content : Container std::pmr::vector

///////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory_resource>
#include <new>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto size = 1uz << 10, alignment = alignof(std::max_align_t);

//  -------------------------------------------------------------------------------------------

    auto array = static_cast < std::byte * > (operator new(size, std::align_val_t(alignment)));

//  -------------------------------------------------------------------------------------------

    std::pmr::monotonic_buffer_resource resource(array, size, std::pmr::new_delete_resource());

//  -------------------------------------------------------------------------------------------

    std::pmr::polymorphic_allocator < int > allocator(&resource);

//  -------------------------------------------------------------------------------------------

    std::pmr::vector < int > vector(allocator);

//  -------------------------------------------------------------------------------------------

    vector = { 1, 2, 3, 4, 5 };

//  -------------------------------------------------------------------------------------------

    auto index = 0uz;

//  -------------------------------------------------------------------------------------------

    for (auto i = 0uz; i < std::size(vector); ++i, index += sizeof(int))
    {
        assert(std::to_integer < int > (array[index]) == vector[i]);
    }

//  -------------------------------------------------------------------------------------------

    vector.push_back(1);

//  -------------------------------------------------------------------------------------------

    for (auto i = 0uz; i < std::size(vector); ++i, index += sizeof(int))
    {
        assert(std::to_integer < int > (array[index]) == vector[i]);
    }

//  -------------------------------------------------------------------------------------------

    operator delete(array, size, std::align_val_t(alignment));
}

///////////////////////////////////////////////////////////////////////////////////////////////