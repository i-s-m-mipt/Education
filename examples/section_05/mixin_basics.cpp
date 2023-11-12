#include <iostream>

struct Number
{
    using value_type = int;

    auto get() const { return value; }
    
    void set(value_type new_value) 
    { 
        value = new_value; 
    }

    value_type value;

}; // struct Number

template < typename Base > struct Undoable : public Base
{
    using value_type = typename Base::value_type;

    void undo() { Base::set(value_before); }
    
    void set(value_type new_value) 
    { 
        value_before = Base::get(); Base::set(new_value); 
    }
    
    value_type value_before;

}; // template < typename Base > struct Undoable : public Base

template < typename Base > struct Redoable : public Base
{
    using value_type = typename Base::value_type;

    void redo() { Base::set(value_after); }
    
    void set(value_type new_value) 
    { 
        value_after = new_value; Base::set(new_value); 
    }
    
    value_type value_after;

}; // template < typename Base > struct Redoable : public Base

int main() 
{
    Redoable < Undoable < Number > > number;

    number.set(42); number.set(84);

    std::cout << number.get() << std::endl; number.undo();
    std::cout << number.get() << std::endl; number.redo();
    std::cout << number.get() << std::endl;

    return 0;
}