//////////////////////////////////////////////////////////////

#include <cassert>
#include <type_traits>

//////////////////////////////////////////////////////////////

template < typename T > void swap(T & x, T & y)
{
    static_assert(std::is_copy_constructible_v < T > );
    
    static_assert(std::is_copy_assignable_v    < T > );

    auto z = y;
            
         y = x;
         
         x = z;
}

//////////////////////////////////////////////////////////////

template < typename T > struct Entity
{
    static_assert(std::is_same_v < T, int > , "T is not int");
};

//////////////////////////////////////////////////////////////

int main()
{
    static_assert(sizeof(int) == 4, "sizeof(int) != 4");

//  ----------------------------------------------------

    [[maybe_unused]] Entity < int   > entity_1;

//  [[maybe_unused]] Entity < int & > entity_2; // error

//  ----------------------------------------------------

    auto x = 1, y = 2;

//  ----------------------------------------------------
        
    swap(x, y);

//  ----------------------------------------------------

    assert(x == 2 && y == 1);
}

//////////////////////////////////////////////////////////////