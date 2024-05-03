#include <iostream>

//  ================================================================================================

class Number
{
public:

    using value_type = int;

    [[nodiscard]] constexpr value_type get() const { return value; }
    
    constexpr void set(value_type new_value) // note: trivial setter for demonstration
    { 
        value = new_value; 
    }

private:

    value_type value{};

}; // class Number

//  ================================================================================================

template < typename Base > class Undoable : public Base
{
public:

    using value_type = typename Base::value_type;

    constexpr void undo() { Base::set(value_before); }
    
    constexpr void set(value_type new_value) 
    { 
        value_before = Base::get(); Base::set(new_value); 
    }

private:
    
    value_type value_before{};

}; // template < typename Base > class Undoable : public Base

//  ================================================================================================

template < typename Base > class Redoable : public Base
{
public:

    using value_type = typename Base::value_type;

    constexpr void redo() { Base::set(value_after); }
    
    constexpr void set(value_type new_value) 
    { 
        value_after = new_value; Base::set(new_value); 
    }
    
private:
    
    value_type value_after{};

}; // template < typename Base > class Redoable : public Base

//  ================================================================================================

int main() 
{
    Redoable < Undoable < Number > > number;

    number.set(42); number.set(84);

    std::cout << number.get() << std::endl; number.undo();
    std::cout << number.get() << std::endl; number.redo();
    std::cout << number.get() << std::endl;

    return 0;
}