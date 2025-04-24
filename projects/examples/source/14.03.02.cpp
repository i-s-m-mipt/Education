///////////////////////////////////////////////////////////////////

#include <atomic>
#include <iostream>
#include <type_traits>

///////////////////////////////////////////////////////////////////

struct alignas(1 * 8) Entity_v1 { int x = 0; };

struct alignas(2 * 8) Entity_v2 { int x = 0; };

///////////////////////////////////////////////////////////////////

class Entity_v3
{
public :

    auto & operator=(Entity_v3 const &)
    {
        std::cout << "Entity_v3::operator=\n";

        return *this;
    }
};

///////////////////////////////////////////////////////////////////

class Entity_v4
{
public :

    virtual ~Entity_v4() = default;
};

///////////////////////////////////////////////////////////////////

class Entity_v5 {};

///////////////////////////////////////////////////////////////////

class Entity_v6 : public virtual Entity_v5 {};

///////////////////////////////////////////////////////////////////

int main()
{
    static_assert(std::is_trivially_copyable_v < Entity_v1 > == 1);

    static_assert(std::is_trivially_copyable_v < Entity_v2 > == 1);

//  ---------------------------------------------------------------

    static_assert(std::is_trivially_copyable_v < Entity_v3 > == 0);

    static_assert(std::is_trivially_copyable_v < Entity_v4 > == 0);

    static_assert(std::is_trivially_copyable_v < Entity_v6 > == 0);

//  ---------------------------------------------------------------

    static_assert(sizeof(Entity_v1) == 1 * 8);

    static_assert(sizeof(Entity_v2) == 2 * 8);

//  ---------------------------------------------------------------

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)

    static_assert(std::atomic < Entity_v1 > ::is_always_lock_free);
    
#endif

//  ---------------------------------------------------------------

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)

    static_assert(std::atomic < Entity_v2 > ::is_always_lock_free);
    
#endif
}

///////////////////////////////////////////////////////////////////