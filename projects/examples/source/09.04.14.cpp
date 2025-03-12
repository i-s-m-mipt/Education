#include <memory_resource>

////////////////////////////////////////////////////

int main()
{
    auto resource = std::pmr::new_delete_resource();

//  ------------------------------------------------

    auto ptr = resource->allocate(4);

    *static_cast < int * > (ptr) = 1;

    resource->deallocate(ptr, 4);
}