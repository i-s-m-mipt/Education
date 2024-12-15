#include <cassert>
#include <cstdlib>
#include <iostream>
#include <type_traits>

//  ================================================================================================

template < typename T > void swap(T & x, T & y)
{
    static_assert(std::is_copy_constructible_v < T > );
    static_assert(std::is_copy_assignable_v    < T > );

    auto z = y; y = x; x = z;
}

//  ================================================================================================

class Bad 
{
private:
 
	Bad() = default; 
};

template < typename T > struct Entity
{
    static_assert(std::is_default_constructible_v < T > , "not default constructible");
};

//  ================================================================================================

void test_v1() { std::cout << "test_v1\n"; }
void test_v2() { std::cout << "test_v2\n"; }

//  ================================================================================================

int main()
{
    auto object = new auto(1);

    assert(object);

    delete object;

//  assert(nullptr); // error

//  --------------------------

           assert(1 + 1 == 2);
    static_assert(1 + 1 == 2);

           assert((sizeof(int) == 4) && "sizeof(int) != 4");
    static_assert((sizeof(int) == 4),   "sizeof(int) != 4");

    [[maybe_unused]] Entity < int > entity_1;
 // [[maybe_unused]] Entity < Bad > entity_2; // error

//  --------------------------------------------------

    std::atexit(test_v1);
    std::atexit(test_v2);

    std::cout << "Terminate normally? (y/n) "; char c; std::cin >> c;

    if (c == 'y') 
    {
        std::exit(0); 
    }
    else 
    {
        std::abort();
    }
}