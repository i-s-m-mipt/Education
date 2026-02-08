///////////////////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling

///////////////////////////////////////////////////////////////////////////////

// section : Irrecoverable Errors

///////////////////////////////////////////////////////////////////////////////

// content : Irrecoverable Errors
//
// content : Compile-Time and Runtime Assertions
//
// content : Declaration static_assert
//
// content : Type Traits std::is_copy_constructible and std::is_copy_assignable
//
// content : Macro assert
//
// content : Debug Information

///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////

template < typename T > void swap(T & x, T & y)
{
    static_assert(std::is_copy_constructible_v < T > );

    static_assert(std::is_copy_assignable_v    < T > );

    auto z = y;

         y = x;

         x = z;
}

///////////////////////////////////////////////////////////////////////////////

template < typename T > struct Entity
{
    static_assert(std::is_same_v < T, int > , "T is not int");
};

///////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(sizeof(int) == 4);

//  ----------------------------------------------------

    auto x = 1, y = 2;

//  ----------------------------------------------------

    swap(x, y);

//  ----------------------------------------------------

    assert(x == 2 && y == 1);

//  ----------------------------------------------------

    [[maybe_unused]] Entity < int   > entity_1;

//  [[maybe_unused]] Entity < int & > entity_2; // error
}

///////////////////////////////////////////////////////////////////////////////