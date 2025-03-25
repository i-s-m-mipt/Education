#include <memory_resource>

////////////////////////////////////////////////////

int main()
{
    auto resource = std::pmr::new_delete_resource();

//  ------------------------------------------------

    auto x = resource->allocate(4);

    *static_cast < int * > (x) = 1;

    resource->deallocate(x, 4);
}