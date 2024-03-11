#include <cassert>
#include <iostream>
#include <type_traits>

template < typename T > void swap(T & a, T & b)
{
    static_assert(
        std::is_copy_constructible_v < T > &&
        std::is_copy_assignable_v    < T > , 
            "swap requires copy constructible type");

    auto c = b; b = a; a = c;
}

struct Bad { Bad() = delete; }; // note: not default constructible

template < typename T = Bad > struct S
{
    static_assert(std::is_default_constructible_v < T > ,
        "S requires default constructible type");

}; // template < typename T = Bad > struct S

void cleanup_v1() { std::cerr << "cleanup_v1 at exit\n"; }
void cleanup_v2() { std::cerr << "cleanup_v2 at exit\n"; }

int main()
{
    auto pointer = new int(42);

    assert(pointer); // good: convenient debugging tool

    delete pointer;

//  assert(nullptr); // error: assertion failed

           assert(2 + 2 == 4); // note: optional message string
    static_assert(2 + 2 == 4); // note: optional message string

           assert((sizeof(int) == 4) && "required size of int 4 bytes");
    static_assert((sizeof(int) == 4),   "required size of int 4 bytes");

    [[maybe_unused]] S < int > good;

//  S bad; // error: static assertion failed

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