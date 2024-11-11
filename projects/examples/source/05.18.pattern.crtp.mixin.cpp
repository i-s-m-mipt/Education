#include <cassert>

//  ================================================================================================

class Entity
{
public:

    using value_type = int;

//  ------------------------------------------------------------------------------------------------

    auto get() const 
    { 
        return m_data; 
    }
    
    void set(int data) 
    { 
        m_data = data;
    }

private:

    int m_data = 0;
};

//  ================================================================================================

template < typename B > class Undoable : public B
{
public:

    using value_type = typename B::value_type;

//  ------------------------------------------------------------------------------------------------

    void undo() 
    { 
        B::set(prev); 
    }
    
    void set(value_type value) 
    { 
        prev = B::get(); B::set(value); 
    }

private:
    
    value_type prev = value_type();
};

//  ================================================================================================

template < typename B > class Redoable : public B
{
public:

    using value_type = typename B::value_type;

//  ------------------------------------------------------------------------------------------------

    void redo() 
    { 
        B::set(next); 
    }
    
    void set(value_type value) 
    { 
        next = value; B::set(value); 
    }
    
private:
    
    value_type next = value_type(); 
};

//  ================================================================================================

int main() 
{
    Redoable < Undoable < Entity > > entity;

    entity.set(1); 
    entity.set(2);

    assert(entity.get() == 2); entity.undo();
    assert(entity.get() == 1); entity.redo();
    assert(entity.get() == 2);
}