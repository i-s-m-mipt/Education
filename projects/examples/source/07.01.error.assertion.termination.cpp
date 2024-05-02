#include <cassert>
#include <cstdlib>
#include <iostream>
#include <type_traits>

//  ================================================================================================

template < typename T > inline constexpr void swap(T & x, T & y)
{
    static_assert(std::is_copy_constructible_v < T > &&
                  std::is_copy_assignable_v    < T > ,  "swap requires copy constructible type");

    const auto z = y; y = x; x = z;
}

//  ================================================================================================

class Bad { public: Bad() = delete; }; // note: not default constructible

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

    assert(object); // good: convenient debugging tool

    delete object;

//  assert(nullptr); // error: assertion failed

//  ================================================================================================

           assert(1 + 1 == 2); // note: optional message string
    static_assert(1 + 1 == 2); // note: optional message string

           assert((sizeof(int) == 4) && "required size of int 4 bytes");
    static_assert((sizeof(int) == 4),   "required size of int 4 bytes");

    [[maybe_unused]] const C < int > good;

//  const C bad; // error: static assertion failed

//  ================================================================================================

    std::atexit(cleanup_v1);
    std::atexit(cleanup_v2);

    std::cout << "Terminate normally? (y/n) "; char c{};

    if (std::cin >> c; c == 'y')
    {
        std::exit(0); // note: termination with exit code, cleanup called
    } 
    else
    {
        std::abort(); // note: abnormal termination, cleanup not called
    }

//	return 0; // warning: unreachable code
}