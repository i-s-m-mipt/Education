#include <cassert>

/////////////////////////////////////////////////

class Entity
{
public:

    using data_t = int;

//  -------------------

    auto get() const 
    { 
        return m_data;
    }
    
    void set(int x) 
    { 
        m_data = x;
    }

private:

    data_t m_data = 0;
};

/////////////////////////////////////////////////

template < typename B > class Undoable : public B
{
public:

    using data_t = typename B::data_t;

//  ----------------------------------

    void set(data_t data) 
    { 
        m_data = B::get();
        
        B::set(data);
    }

    auto & undo() 
    { 
        B::set(m_data);

        return *this;
    }
    
private:
    
    data_t m_data = data_t();
};

/////////////////////////////////////////////////

template < typename B > class Redoable : public B
{
public:

    using data_t = typename B::data_t;

//  ----------------------------------

    void set(data_t data) 
    { 
        m_data = data;
        
        B::set(data);
    }

    auto & redo() 
    { 
        B::set(m_data);

        return *this;
    }
    
private:
    
    data_t m_data = data_t();
};

/////////////////////////////////////////////////

int main() 
{
    Redoable < Undoable < Entity > > entity;

//  ----------------------------------------

    for (auto i = 0; i < 2; ++i)
    {
        entity.set(i + 1);
    }

//  ----------------------------------------

    assert(entity.undo().get() == 1);

    assert(entity.redo().get() == 2);
}