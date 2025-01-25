#include <cassert>

/////////////////////////////////////////////////

class Entity
{
public:

    using data_t = int;

//  -----------------------

    auto get() const 
    { 
        return m_data; 
    }
    
    void set(int data) 
    { 
        m_data = data;
    }

private:

    data_t m_data = 0;
};

/////////////////////////////////////////////////

template < typename B > class Undoable : public B
{
public:

    using data_t = typename B::data_t;

//  ---------------------------------------------

    void set(data_t data) 
    { 
        m_data = B::get(); B::set(data); 
    }

    void undo() 
    { 
        B::set(m_data); 
    }
    
private:
    
    data_t m_data = data_t();
};

/////////////////////////////////////////////////

template < typename B > class Redoable : public B
{
public:

    using data_t = typename B::data_t;

//  ---------------------------------------------

    void set(data_t data) 
    { 
        m_data = data; B::set(data); 
    }

    void redo() 
    { 
        B::set(m_data); 
    }
    
private:
    
    data_t m_data = data_t(); 
};

/////////////////////////////////////////////////

int main() 
{
    Redoable < Undoable < Entity > > entity;

//  -----------------------------------------

    entity.set(1); 
    
    entity.set(2);

//  -----------------------------------------

    entity.undo(); assert(entity.get() == 1);

    entity.redo(); assert(entity.get() == 2);
}