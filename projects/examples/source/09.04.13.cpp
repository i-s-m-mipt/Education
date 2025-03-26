#include <algorithm>
#include <array>
#include <cassert>
#include <memory_resource>
#include <string_view>
#include <vector>

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////

int main()
{
    constexpr auto size = 32uz;

    std::array < char, size > array = {};

    std::ranges::fill(array, '_');

    std::pmr::monotonic_buffer_resource resource(std::data(array), size);

    std::pmr::vector < char > vector(26, '\0', &resource);

//  ---------------------------------------------------------------------

    for (auto i = 0uz; i < std::size(vector); ++i)
    {
        vector[i] = 'a' + i;
    }

//  ---------------------------------------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        assert(array[i] == "abcdefghijklmnopqrstuvwxyz______"sv[i]);
    }
}