#include <cassert>
#include <cstdlib>
#include <iostream>
#include <type_traits>

//  ================================================================================================

template < typename T > inline constexpr void swap(T & x, T & y)
{
    static_assert(std::is_copy_constructible_v < T > && std::is_copy_assignable_v < T > );

    const auto z = y; y = x; x = z;
}

//  ================================================================================================

class Bad { public: Bad() = delete; };

template < typename T = Bad > class C
{
public: static_assert(std::is_default_constructible_v < T > , "not default constructible");
};

//  ================================================================================================

inline void cleanup_v1() { std::cerr << "cleanup_v1 at exit\n"; }
inline void cleanup_v2() { std::cerr << "cleanup_v2 at exit\n"; }

//  ================================================================================================

int main()
{
    const auto object = new const auto(42);

    assert(object);

    delete object;

//  assert(nullptr); // error

//  ================================================================================================

           assert(1 + 1 == 2);
    static_assert(1 + 1 == 2);

           assert((sizeof(int) == 4) && "required sizeof(int) == 4");
    static_assert((sizeof(int) == 4),   "required sizeof(int) == 4");

    [[maybe_unused]] const C < int > good;

//  const C bad; // error

//  ================================================================================================

    std::atexit(cleanup_v1);
    std::atexit(cleanup_v2);

    std::cout << "Terminate normally? (y/n) "; char c{}; std::cin >> c;

    if (c == 'y') std::exit(0); else std::abort();

	return 0;
}