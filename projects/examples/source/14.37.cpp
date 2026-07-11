///////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

///////////////////////////////////////////////////////////////////////////////////////////////////

// content : Atomic Compatible Types
//
// content : Type Trait std::is_trivially_copyable
//
// content : Type Traits std::is_move_constructible and std::is_move_assignable
//
// content : Metafunction std::remove_cv
//
// content : Instruction Compare-And-Swap (CAS)
//
// content : Macro __GCC_HAVE_SYNC_COMPARE_AND_SWAP_X

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <print>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////////////

struct alignas(1 * 8) Entity_v1 { int x = 0; };

struct alignas(2 * 8) Entity_v2 { int x = 0; };

///////////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v3
{
public :

    auto & operator=(Entity_v3 const &)
    {
        std::print("Entity_v3::operator=\n");

        return *this;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v4
{
public :

   ~Entity_v4() {};
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v5
{
public :

    virtual ~Entity_v5() = default;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v6 : public virtual Entity_v5 {};

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class is_atomic_compatible : public std::integral_constant
<
    bool,

    std::is_trivially_copyable_v < T > &&

    std::is_copy_constructible_v < T > && std::is_copy_assignable_v < T > &&

    std::is_move_constructible_v < T > && std::is_move_assignable_v < T > &&

    std::is_same_v < T, std::remove_cv_t < T > >

> {};

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > constexpr auto is_atomic_compatible_v = is_atomic_compatible < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(is_atomic_compatible_v < Entity_v1 > == 1);

    static_assert(is_atomic_compatible_v < Entity_v2 > == 1);

    static_assert(is_atomic_compatible_v < Entity_v3 > == 0);

    static_assert(is_atomic_compatible_v < Entity_v4 > == 0);

    static_assert(is_atomic_compatible_v < Entity_v5 > == 0);

    static_assert(is_atomic_compatible_v < Entity_v6 > == 0);

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

///////////////////////////////////////////////////////////////////////////////////////////////////