#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory_resource>
#include <vector>

int main()
{
    std::array < char, 64 > buffer{}; // note: external arena stack buffer for pool

    std::ranges::fill_n(std::begin(buffer), std::size(buffer), '_');

    std::pmr::monotonic_buffer_resource pool(std::data(buffer), std::size(buffer));

    const std::size_t size = 26;

    std::pmr::vector < char > vector(&pool); // note: type alias

    for (std::size_t i = 0; i < size; ++i)
    {
        vector.push_back(static_cast < char > ('a' + i));
    }

    for (auto element : buffer) std::cout << element; // note: outputs repeated data in buffer

    auto resource = std::pmr::new_delete_resource();

    auto pointer = resource->allocate(1); // note: same as ::operator new

    resource->deallocate(pointer, 1); // note: same as ::operator delete

	return 0;
}
